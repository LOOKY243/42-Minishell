/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:38:17 by ycostode          #+#    #+#             */
/*   Updated: 2024/04/18 15:58:29 by gmarre           ###   ########.fr       */
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
