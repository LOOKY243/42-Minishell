/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/03/21 14:36:43 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmds(t_program program, char *cmd)
{
	int		i;
	char	*path;
	char	**env;
	char	*tmp;

	if (!cmd)
		return (NULL);
	if (!find_variable(program.envp, "PATH="))
		return (cmd);
	i = 0;
	env = ft_split_cmd(find_variable(program.envp, "PATH="), ':');
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
	ft_freesplit(env);
	return (cmd);
}

int	treat_command(t_program *program, char *cmd)
{
	char	**args;
	int		value;

	args = ft_split_cmd(cmd, ' ');
	remove_quote_split(1, args);
	args[0] = get_cmds(*program, args[0]);
	if (args[0])
	{
		close(program->pipe[1]);
		close(program->pipe[0]);
		value = execve(args[0], args, program->envp);;
		print_error(args[0], value);
	}
	ft_freesplit(args);
	return (127);
}

int	treat_command_recoded(t_program *program, int fd, char *cmd)
{
	char	**args;
	int		value;

	args = ft_split_cmd(cmd, ' ');
	remove_quote_split(1, args);
	value = ENOENT;
	if (ft_strcmp(args[0], "echo") == 0)
		value = echo(args, fd);
	else if (ft_strcmp(args[0], "pwd") == 0)
		value = pwd(fd);
	else if (ft_strcmp(args[0], "env") == 0)
		value = env(program->envp, fd);
	else if (ft_strcmp(args[0], "export") == 0)
		value = export(program, args, fd);
	else if (ft_strcmp(args[0], "$?") == 0)
		value = return_value(program->exit_value);
	else if (ft_strcmp(args[0], "unset") == 0)
		value = unset(program, args);
	else if (ft_strcmp(args[0], "cd") == 0)
		value = cd(program, args[1]);
	if (value != 0)
		print_strerror(args[0], value, value);
	ft_freesplit(args);
	return (value);
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
		close(program->pipe[PIPE_READ]);
}

void	treat_child_recoded(t_program *program, char *cmd, int current, int max)
{
	if (max != 0)
	{
		if (current == 0)
			program->exit_value = treat_command_recoded(program,
					program->pipe[PIPE_WRITE], cmd);
		else if (current == max)
			program->exit_value = treat_command_recoded(program,
					program->outfile, cmd);
		else
			program->exit_value = treat_command_recoded(program,
					program->pipe[PIPE_WRITE], cmd);
	}
	else
		program->exit_value = treat_command_recoded(program, program->outfile,
				cmd);
	if (program->exit_value != 0)
		close(program->pipe[PIPE_READ]);
}

bool	is_recoded(char *cmd)
{
	char	**args;
	bool	recoded;

	args = ft_split_cmd(cmd, ' ');
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
