/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 16:13:15 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	(void)signal;
	write(0, "\n", 1);
	g_exterminate = 1;
}

int	read_stdin3(t_program *program, char *tmp)
{
	if (write(program->infile, tmp, ft_strlen(tmp)) != (int)ft_strlen(tmp))
	{
		print_error("write", EXIT_FAILURE);
		return (0);
	}
	write(program->infile, "\n", 1);
	free(tmp);
	return (1);
}

int	read_stdin2_bis(char *buffer)
{
	if (buffer == NULL)
	{
		print_fd(STDOUT_FILENO, "minishit: warning: here-document \
at line 3 delimited by end-of-file (wanted 'eof')\n");
		return (0);
	}
	return (1);
}

void	read_stdin2(t_program *program, char *limit, char *limiter,
		int is_quoted)
{
	char	*tmp;
	char	*buffer;

	while (g_exterminate != 1)
	{
		buffer = readline("\x1b[0mheredoc> ");
		if (!read_stdin2_bis(buffer))
			break ;
		if (!is_quoted)
		{
			tmp = change_cmd_var(*program, buffer);
			if (!ft_strcmp(buffer, limiter))
			{
				free(tmp);
				break ;
			}
		}
		else if (!ft_strncmp(buffer, &limit[1], ft_strlen(&limit[1]) - 1))
			break ;
		else
			tmp = ft_strdup(buffer);
		if (!read_stdin3(program, tmp))
			break ;
	}
}

void	read_stdin(t_program *program, char *limit)
{
	int		is_quoted;
	char	*limiter;

	signal(SIGINT, sigint_handler);
	if (program->infile)
		close(program->infile);
	if (!strcmp(limit, ""))
		return ;
	program->random_file = random_string(program, 10);
	program->infile = open(program->random_file, O_CREAT | O_WRONLY | O_TRUNC,
			0666);
	is_quoted = is_double_quoted(limit);
	limiter = remove_quotes(limit);
	read_stdin2(program, limit, limiter, is_quoted);
	close(program->infile);
	program->infile = open(program->random_file, O_RDONLY);
	free(limiter);
}
