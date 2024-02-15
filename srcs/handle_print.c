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
	return (value);
}

int	print_fd(int fd, char *str, int value)
{
	write(fd, str, ft_strlen(str));
	return (value);
}

void	print(const char *s)
{
	write(1, s, ft_strlen(s));
}