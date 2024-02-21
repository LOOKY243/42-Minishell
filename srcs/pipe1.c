/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/21 14:37:09 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_program *program, char *cmd)
{
	pid_t	pid;

	if (pipe(program->pipe) == -1 || pipe(program->data_pipe) == -1)
		return (print_error("\x1b[1;6;31mpipe", EXIT_FAILURE));
	if (!is_recoded(cmd))
	{
		pid = fork();
		if (pid == -1)
			return (print_error("\x1b[1;6;31mfork", EXIT_FAILURE));
		program->pid[program->cmd.current] = pid;
		if (pid == 0)
		{
			treat_child(program, cmd, program->cmd.current, program->cmd.len - 1);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, NULL, 0);
	}
	else
		treat_child_no_fork(program, cmd, program->cmd.current, program->cmd.len - 1);
	if (program->pipe_saved != -1)
		close(program->pipe_saved);
	program->pipe_saved = program->pipe[PIPE_READ];
	close(program->pipe[PIPE_WRITE]);
	return (EXIT_SUCCESS);
}

int	size_list(char **list)
{
	int	i;

	if (!list)
		return (0);
	i = 0;
	while(list[i])
		++i;
	return (i);
}

void	process(char *prompt, t_program *program)
{
	program->cmd.current = 0;
	program->cmd.list = ft_split(prompt, '|');
	program->cmd.len = size_list(program->cmd.list);
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
	//wait_child(*program);
}