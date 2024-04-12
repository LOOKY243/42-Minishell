/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:38:17 by ycostode          #+#    #+#             */
/*   Updated: 2024/04/10 13:29:34 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *str, int value)
{
	print_fd(STDERR_FILENO, "\x1b[1;31mminishit: ");
	perror(str);
	print_fd(STDERR_FILENO, "\x1b[0m");
	return (value);
}

int	print_strerror(char *str, int errnum, int value)
{
	char	*error;

	error = strerror(errnum);
	print_fd(STDERR_FILENO, "\x1b[1;31mminishit: ");
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, error, ft_strlen(error));
	print_fd(STDERR_FILENO, "\x1b[0m\n");
	return (value);
}

void	print(const char *s)
{
	write(STDOUT_FILENO, s, ft_strlen(s));
}

void	print_fd(int fd, const char *s)
{
	write(fd, s, ft_strlen(s));
}

void	print_prompt(char *s)
{
	int	i;
	int	index;

	i = -1;
	index = -1;
	while (s[++i])
	{
		if (s[i] == '/')
			index = i;
	}
	printf("%.*s", index + 1, s);
	printf("\x1b[1;34m%s", &s[index + 1]);
	free(s);
}

void	modify_prompt(const char *s)
{
	print("\x1b[1A\x1b[0K");
	print("\x1b[1A\x1b[0K");
	print("\x1b[1A\x1b[0K");
	print("\x1b[1;33m❯\x1b[0m ");
	print(s);
	print("\n");
}
