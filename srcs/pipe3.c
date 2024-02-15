/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <ycostode@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:37:06 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/09 16:37:06 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dups(int stdinfd, int stdoutfd)
{
	dup2(stdinfd, STDIN_FILENO);
	dup2(stdoutfd, STDOUT_FILENO);
	close(stdinfd);
	close(stdoutfd);
}

static char	*get_cmds(t_pipex pipex, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	if (!cmd)
		return (NULL);
	if (!pipex.env)
		return (cmd);
	i = 0;
	while (pipex.env[i])
	{
		path = ft_strdup(pipex.env[i]);
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

static void	exec_cmd(t_pipex pipex, char *cmd)
{
	char	**args;

	args = ft_split_cmd(cmd, ' ');
	args[0] = get_cmds(pipex, args[0]);
	execve(args[0], args, pipex.envp);
	ft_freesplit(args);
}

bool	treat_child(t_pipex *pipex, char *cmd, int current, int max)
{
	if (current == 0)
		dups(pipex->infile, pipex->pipe[PIPE_WRITE]);
	else if (current == max)
		dups(pipex->pipe_saved, pipex->outfile);
	else
		dups(pipex->pipe_saved, pipex->pipe[PIPE_WRITE]);
	close(pipex->pipe[PIPE_WRITE]);
	exec_cmd(*pipex, cmd);
	close(pipex->pipe[PIPE_READ]);
	return (print_error("\033[1;31mexecve", false));
}