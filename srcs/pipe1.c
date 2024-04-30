/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/04/30 12:18:35 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_only_spaces(char *str)
{
	int		i;
	char	*cpy;

	i = -1;
	cpy = remove_quotes(str);
	if (!ft_strlen(cpy))
	{
		free(cpy);
		return (0);
	}
	while (cpy[++i])
	{
		if (cpy[i] != ' ')
		{
			free(cpy);
			return (1);
		}
	}
	free(cpy);
	return (0);
}

int	exec_non_recoded(char *new_cmd, t_program *program)
{
	pid_t	pid;

	program->exit_value = 0;
	pid = fork();
	program->pid[program->cmd.current] = pid;
	if (pid == -1)
		return (print_error("fork", EXIT_FAILURE));
	if (pid == 0)
	{
		treat_child(program, new_cmd, program->cmd.current, program->cmd.len
			- 1);
		free_child(program, new_cmd);
		exit(program->exit_value);
	}
	return (0);
}

int	exec(t_program *program, char *cmd)
{
	char	*new_cmd;

	if (pipe(program->pipe) == -1)
		return (print_error("pipe", EXIT_FAILURE));
	new_cmd = treat_cmd(*program, cmd);
	if (!check_only_spaces(cmd))
	{
		free(new_cmd);
		return (EXIT_FAILURE);
	}
	else if (!is_recoded(new_cmd))
	{
		if (exec_non_recoded(new_cmd, program) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
		treat_child_recoded(program, new_cmd, program->cmd.current,
			program->cmd.len - 1);
	free(new_cmd);
	if (program->pipe_saved != -1)
		close(program->pipe_saved);
	program->pipe_saved = program->pipe[PIPE_READ];
	close(program->pipe[PIPE_WRITE]);
	return (EXIT_SUCCESS);
}

void	launch_commands(t_program *program)
{
	while (program->cmd.list[program->cmd.current])
	{
		if (exec(program, program->cmd.list[program->cmd.current]))
			break ;
		program->cmd.current++;
	}
}

void	process(char *prompt, t_program *program)
{
	program->cmd.current = 0;
	program->cmd.list = ft_split_cmd(prompt, '|');
	program->cmd.len = count_args_no_sign(program->cmd.list);
	program->pipe_saved = -1;
	if (multi_stuck_pipes(prompt))
		return ((void)ft_freesplit(program->cmd.list));
	if (!handle_file(program))
		return ((void)ft_freesplit(program->cmd.list));
	if (program->infile == -1 || program->outfile == -1)
	{
		close_file(program->infile, program->outfile);
		ft_freesplit(program->cmd.list);
		return ;
	}
	launch_commands(program);
	if (program->random_file)
		unlink(program->random_file);
	program->random_file = NULL;
	close_fd(*program);
	if (program->cmd.current != 0)
		wait_child(program);
	ft_freesplit(program->cmd.list);
}
