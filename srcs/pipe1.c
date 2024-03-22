/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/03/22 13:06:00 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_program *program, char *cmd)
{
	pid_t	pid;
	char	*new_cmd;

	if (pipe(program->pipe) == -1)
		return (print_error("pipe", EXIT_FAILURE));
	new_cmd = treat_cmd(*program, cmd);
	if (!is_recoded(new_cmd))
	{
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

void	process(char *prompt, t_program *program)
{
	program->cmd.current = 0;
	program->cmd.list = ft_split_cmd(prompt, '|');
	program->cmd.len = count_args_no_sign(program->cmd.list);
	program->pipe_saved = -1;
	handle_file(program);
	if (program->infile == -1 || program->outfile == -1)
	{
		close_file(program->infile, program->outfile);
		ft_freesplit(program->cmd.list);
		return ;
	}
	while (program->cmd.list[program->cmd.current])
	{
		if (exec(program, program->cmd.list[program->cmd.current]))
			break ;
		program->cmd.current++;
	}
	if (program->random_file)
		unlink(program->random_file);
	program->random_file = NULL;
	close_fd(*program);
	ft_freesplit(program->cmd.list);
	wait_child(program);
}
