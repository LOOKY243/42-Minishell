/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:45:00 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/17 17:23:45 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_errors(t_program *program, t_handle_file *h_file)
{
	if (h_file->i == h_file->len - 1)
	{
		if (is_command_sign(h_file->cut[h_file->i]))
		{
			free_result(h_file->cut, h_file->len);
			print_fd(2, "minishit: syntax error near \
unexpected token 'newline'\n");
			close(program->infile);
			return (0);
		}
	}
	else if (is_command_sign(h_file->cut[h_file->i])
		&& is_command_sign(h_file->cut[h_file->i + 1]))
	{
		if (h_file->j == program->cmd.len - 1)
			print_fd(2, "minishit: syntax error near \
unexpected token 'newline'\n");
		else
			print_fd(2, "minishit: syntax error \
near unexpected token '|'\n");
		free_result(h_file->cut, h_file->len);
		close(program->infile);
		return (0);
	}
	return (1);
}

int	append_file(t_program *program, t_handle_file *h_file)
{
	if (!ft_strcmp(h_file->cut[h_file->i], ">>"))
	{
		if (open_file(program, h_file->cut[h_file->i + 1], 1) == -1)
		{
			free_result(h_file->cut, h_file->len);
			return (0);
		}
		return (2);
	}
	return (1);
}

int	is_infile(t_program *program, t_handle_file *h_file)
{
	if (!ft_strcmp(h_file->cut[h_file->i], "<"))
	{
		if (h_file->i == h_file->len - 1)
		{
			print_fd(2, "minishit: syntax error near \
unexpected token 'newline'\n");
			free_result(h_file->cut, h_file->len);
			return (0);
		}
		if (open_file(program, h_file->cut[h_file->i + 1], 2) == -1)
		{
			free_result(h_file->cut, h_file->len);
			return (0);
		}
		return (2);
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

int	is_outfile(t_program *program, t_handle_file *h_file)
{
	if (!ft_strcmp(h_file->cut[h_file->i], ">"))
	{
		if (h_file->i == h_file->len - 1)
		{
			print_fd(2, "minishit: syntax error near \
unexpected token 'newline'\n");
			free_result(h_file->cut, h_file->len);
			return (0);
		}
		if (open_file(program, h_file->cut[h_file->i + 1], 3) == -1)
		{
			free_result(h_file->cut, h_file->len);
			return (0);
		}
		return (2);
	}
	return (1);
}

int	handle_file2(t_program *program, t_handle_file *h_file, int *trigger)
{
	int	val;

	val = check_file_errors(program, h_file);
	if (val == 0)
		return (0);
	if (!ft_strcmp(h_file->cut[h_file->i], "<<"))
	{
		read_stdin(program, h_file->cut[h_file->i + 1]);
		return (1);
	}
	val = append_file(program, h_file);
	if (val == 0)
		return (0);
	else if (val == 2)
		return (1);
	val = is_infile(program, h_file);
	if (val == 2)
		return (2);
	val = is_outfile(program, h_file);
	if (val == 0)
		return (0);
	else if (val == 2)
		return (1);
	*trigger = 0;
	return (1);
}

int	handle_file(t_program *program)
{
	t_handle_file	h_file;
	int				trigger;

	h_file.j = -1;
	program->infile = STDIN_FILENO;
	program->outfile = STDOUT_FILENO;
	if (program->cmd.len == 0)
		print_fd(2, "minishit: syntax error near unexpected token '|'\n");
	while (program->cmd.list[++h_file.j])
	{
		h_file.cut = custom_split(program->cmd.list[h_file.j], &h_file.len);
		h_file.i = -1;
		while (++h_file.i < h_file.len)
		{
			trigger = 1;
			if (!handle_file2(program, &h_file, &trigger))
				return (0);
			free_close_args(program, &h_file, trigger);
		}
		free(program->cmd.list[h_file.j]);
		program->cmd.list[h_file.j] = join_rest(h_file.cut, h_file.len);
		free_result(h_file.cut, h_file.len);
	}
	return (1);
}
