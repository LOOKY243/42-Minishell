/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:17:22 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 16:17:55 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_file_errors2(t_program *program, t_handle_file *h_file)
{
	if (h_file->j == program->cmd.len - 1)
		print_fd(2, "minishit: syntax error near \
unexpected token 'newline'\n");
	else
		print_fd(2, "minishit: syntax error \
near unexpected token '|'\n");
	free_result(h_file->cut, h_file->len);
	if (program->infile != STDIN_FILENO)
		close(program->infile);
}

int	check_file_errors(t_program *program, t_handle_file *h_file)
{
	if (h_file->i == h_file->len - 1)
	{
		if (is_command_sign(h_file->cut[h_file->i]))
		{
			free_result(h_file->cut, h_file->len);
			print_fd(2, "minishit: syntax error near \
unexpected token 'newline'\n");
			if (program->infile != STDIN_FILENO)
				close(program->infile);
			return (0);
		}
	}
	else if (is_command_sign(h_file->cut[h_file->i])
		&& is_command_sign(h_file->cut[h_file->i + 1]))
	{
		check_file_errors2(program, h_file);
		return (0);
	}
	return (1);
}

void	free_close_args(t_program *program, t_handle_file *h_file, int trigger)
{
	if (trigger)
	{
		free(h_file->cut[h_file->i]);
		free(h_file->cut[h_file->i + 1]);
		h_file->cut[h_file->i] = 0;
		h_file->cut[h_file->i + 1] = 0;
	}
	if (program->random_file)
	{
		unlink(program->random_file);
		free(program->random_file);
	}
	program->random_file = 0;
}
