/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:15:55 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 16:16:31 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_recoded(char *cmd)
{
	char	**args;
	char	*command;
	bool	recoded;

	args = ft_split_cmd(cmd, ' ');
	command = remove_quotes(args[0]);
	free(args[0]);
	args[0] = command;
	recoded = false;
	if (ft_strcmp(args[0], "echo") == 0)
		recoded = true;
	else if (ft_strcmp(args[0], "pwd") == 0 && !args[1])
		recoded = true;
	else if (ft_strcmp(args[0], "cd") == 0)
		recoded = true;
	else if (ft_strcmp(args[0], "env") == 0 && !args[1])
		recoded = true;
	else if (ft_strcmp(args[0], "export") == 0)
		recoded = true;
	else if (ft_strcmp(args[0], "unset") == 0)
		recoded = true;
	ft_freesplit(args);
	return (recoded);
}

char	*get_cmds2(char **env, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (env[i])
	{
		path = ft_strdup(env[i]);
		tmp = ft_strjoin(path, "/");
		free(path);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) != -1)
		{
			ft_freesplit(env);
			return (path);
		}
		free(path);
		++i;
	}
	return (NULL);
}

char	*get_cmds(t_program program, char *cmd)
{
	char	**env;
	char	*path;

	if (!cmd)
		return (NULL);
	if (!find_variable(program.envp, "PATH="))
		return (cmd);
	env = ft_split_cmd(find_variable(program.envp, "PATH="), ':');
	path = get_cmds2(env, cmd);
	if (path != NULL)
		return (path);
	ft_freesplit(env);
	return (cmd);
}
