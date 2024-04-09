/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/04/09 17:17:16 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dups(int stdinfd, int stdoutfd)
{
	if (stdinfd != STDIN_FILENO)
	{
		dup2(stdinfd, STDIN_FILENO);
		close(stdinfd);
	}
	if (stdoutfd != STDOUT_FILENO)
	{
		dup2(stdoutfd, STDOUT_FILENO);
		close(stdoutfd);
	}
}

void	close_file(int infile, int oufile)
{
	if (infile != -1)
	{
		perror("infile");
		close(infile);
	}
	if (oufile != -1)
	{
		perror("outfile");
		close(oufile);
	}
}

void	close_fd(t_program program)
{
	if (program.pipe_saved != -1)
		close(program.pipe_saved);
	if (program.infile != STDIN_FILENO)
		close(program.infile);
	if (program.outfile != STDOUT_FILENO)
		close(program.outfile);
}

void	wait_child(t_program *program)
{
	int	i;
	int status;

	i = 0;
	while (i < program->cmd.len)
	{
		if (!is_recoded(program->cmd.list[i]))
		{
			waitpid(program->pid[i], &status, 0);
			program->exit_value = WEXITSTATUS(program->exit_value);
		}
		++i;
	}
}
