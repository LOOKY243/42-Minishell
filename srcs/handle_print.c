/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <ycostode@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:38:17 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/09 16:45:18 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *str, int value)
{
	perror(str);
	print("\x1b[0m");
	return (value);
}

int	print_strerror(char *str, int errnum, int value)
{
	char *error;

	error = strerror(errnum);
	print("\x1b[1;31m");
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error, ft_strlen(error));
	print("\x1b[0m\n");
	return (value);
}

void	print(const char *s)
{
	write(STDOUT_FILENO, s, ft_strlen(s));
}

void	print_prompt(char *s)
{
	int	i;
	int	index;

	i = -1;
	index = -1;
	while (s[++i]) {
		if (s[i] == '/')
			index = i;
	}
	printf("%.*s", index + 1, s);
	printf("\x1b[1;34m%s", &s[index + 1]);
	free(s);
}

void	modify_prompt(const char *s)
{
	print("\x1b[1A\x1b[0K"); //go to and clean empty line
	print("\x1b[1A\x1b[0K"); //go to and clean ╰─ command
	print("\x1b[1A\x1b[0K"); //go to and clean ╭─ header
	print("\x1b[1;33m❯\x1b[0m ");
	print(s);
	print("\n");
}