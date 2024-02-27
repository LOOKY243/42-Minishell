/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/26 13:37:53 by gmarre           ###   ########.fr       */
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

int	treat_command(t_program *program, char *cmd)
{
	char	**args;

	args = ft_split_cmd(cmd, ' ');
	args[0] = get_cmds(*program, args[0]);
	if (args[0])
		return (execve(args[0], args, program->envp));
	ft_freesplit(args);
	return (127);
}

int	treat_command_recoded(t_program *program, char *cmd)
{
	char	**args;

	args = ft_split_cmd(cmd, ' ');
	if (ft_strcmp(args[0], "echo") == 0 && ft_strcmp(args[1], "-n") == 0)
		return (echo(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd(program->envp));
	if (ft_strcmp(args[0], "env") == 0)
		return (env(program->envp));
	if (ft_strcmp(args[0], "export") == 0)
		return (export(program, args));
	if (ft_strcmp(args[0], "$?") == 0)
		return (return_value(program->exit_value));
	if (ft_strcmp(args[0], "unset") == 0)
	{
		unset(program, args);
		return (0);
	}
	if (ft_strcmp(args[0], "cd") == 0)
		return (cd(program->envp, args[1]));
	return (ENOENT);
}

void	treat_child(t_program *program, char *cmd, int current, int max)
{
	if (max != 0)
	{
		if (current == 0)
			dups(program->infile, program->pipe[PIPE_WRITE]);
		else if (current == max)
			dups(program->pipe_saved, program->outfile);
		else
			dups(program->pipe_saved, program->pipe[PIPE_WRITE]);
	}
	else
		dups(program->infile, program->outfile);
	close(program->pipe[PIPE_WRITE]);
	program->exit_value = treat_command(program, cmd);
	if (program->exit_value != 0)
	{
		close(program->pipe[PIPE_READ]);
		print_error("\x1b[1;6;31mexecve", program->exit_value);
	}
}

void	treat_child_recoded(t_program *program, char *cmd, int current, int max)
{
	if (max != 0)
	{
		if (current == 0)
			dups(program->infile, program->pipe[PIPE_WRITE]);
		else if (current == max)
			dups(program->pipe_saved, program->outfile);
		else
			dups(program->pipe_saved, program->pipe[PIPE_WRITE]);
	}
	else
		dups(program->infile, program->outfile);
	close(program->pipe[PIPE_WRITE]);
	program->exit_value = treat_command_recoded(program, cmd);
	if (program->exit_value != 0)
	{
		close(program->pipe[PIPE_READ]);
		print_strerror("\x1b[1;6;31mbuilt-ins: ", program->exit_value, -1);
	}
}

bool    is_recoded(char *cmd)
{
	char	**args;
	bool recoded;

	args = ft_split_cmd(cmd, ' ');
	recoded = false;
	if (ft_strcmp(args[0], "echo") == 0 && ft_strcmp(args[1], "-n") == 0)
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