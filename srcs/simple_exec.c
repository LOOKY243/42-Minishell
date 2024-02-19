/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:20:50 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/16 18:24:10 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmds(t_program program, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	if (!cmd)
		return (NULL);
	if (!program.path)
		return (cmd);
	i = 0;
	while (program.path[i])
	{
		path = ft_strdup(program.path[i]);
		tmp = ft_strjoin(path, "/");
		free(path);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) != -1)
			return (path);
		free(path);
		++i;
	}
	return (cmd);
}

void    simple_exec(char **cmd, t_program program)
{
    cmd[0] = get_cmds(program, cmd[0]);
    execve(cmd[0], cmd, program.envp);
}
