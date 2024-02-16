/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/16 11:37:33 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_home(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

static char	*home_pwd(char **envp)
{
	char	*current;
	char	*home;
	char	*final;

	current = ft_strdup(find_pwd(envp));
	home = find_home(envp);
	if (ft_strncmp(home, current, ft_strlen(home)) != 0)
		return (current);
	final = ft_strjoin("~", &current[ft_strlen(home)]);
	if (current)
		free(current);
	return (final);
}

static char	*session(char **envp)
{
	int	i;
	char	*line;
	char	**split;

	i = 0;
	line = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SESSION_MANAGER=", 16) == 0)
		{
			line = &envp[i][16];
			break;
		}
		i++;
	}
	if (!line)
		return (NULL);
	split = ft_split_cmd(line, '/');
	if (split && split[0] && split[1])
	{
		line = ft_calloc(4, sizeof(char));
		ft_strlcpy(line, split[1], 4);
	}
	ft_freesplit(split);
	return (line);
}

static char	*log_name(char	**envp)
{
	int	i;
	char	*line;
	char	*tmp;
	char	*post;

	line = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "LOGNAME=", 8) == 0)
		{
			line = &envp[i][8];
			break;
		}
		i++;
	}
	if (!line)
		return (NULL);
	tmp = ft_strjoin(line, "@");
	post = session(envp);
	line = ft_strjoin(tmp, post);
	free (tmp);
	if (post)
		free(post);
	return (line);
}

char	*prompt(char **envp)
{
	char	*log;
	char	*current;
	char	*prompt;
	char	*tmp;

	log = log_name(envp);
	current = home_pwd(envp);
	prompt = ft_strdup("\x1b[1;30m╭─\x1b[0;30m░▒▓\x1b[0;37;40m  \x1b[1;30m\x1b[0;34;40m  ");
	tmp = ft_strjoin(prompt, current);
	if (current)
		free(current);
	free(prompt);
	prompt = ft_strjoin(tmp, " \x1b[1;30m\x1b[0;93;40m ");
	free(tmp);
	tmp = ft_strjoin(prompt, log);
	if (log)
		free(log);
	free(prompt);
	prompt = ft_strjoin(tmp, " \x1b[0m\x1b[30m\x1b[0m\n");
	free(tmp);
	return (prompt);
}