/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/03/20 16:22:17 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*home_pwd(char **envp)
{
	char	*current;
	char	*pwd;
	char	*home;
	char	*final;

	pwd = getcwd(NULL, 0);
	current = ft_strdup(pwd);
	home = find_variable_secure(envp, "HOME=");
	if (!home)
		return (ft_strdup("/home"));
	if (ft_strncmp(home, current, ft_strlen(home)) != 0)
		return (current);
	final = ft_strjoin("~", &current[ft_strlen(home)]);
	if (current)
		free(current);
	free(pwd);
	return (final);
}

static char	*session(char **envp)
{
	char	*line;
	char	**split;

	line = find_variable_secure(envp, "SESSION_MANAGER=");
	if (!line)
		return (ft_strdup("1A1"));
	split = ft_split_cmd(line, '/');
	if (split && split[0] && split[1])
	{
		line = ft_calloc(4, sizeof(char));
		ft_strlcpy(line, split[1], 4);
	}
	ft_freesplit(split);
	return (line);
}

static char	*log_name(char **envp)
{
	char	*line;
	char	*tmp;
	char	*post;

	line = find_variable_secure(envp, "LOGNAME=");
	if (!line)
		return (ft_strdup("logname@1A1"));
	tmp = ft_strjoin(line, "@");
	post = session(envp);
	line = ft_strjoin(tmp, post);
	free(tmp);
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
	print("\x1b[0m");
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
