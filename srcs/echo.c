/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:03:50 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/13 16:42:59 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && ft_strcmp(arr[i], "|"))
		i++;
	return (i);
}

int	count_args_no_sign(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	echo(char **cmd, int fd)
{
	int	i;

	i = 2;
	while (cmd[i] && ft_strcmp(cmd[i], "|"))
	{
		print_fd(fd, cmd[i]);
		if (i != count_args(cmd) - 1)
			print_fd(fd, " ");
		i++;
	}
	return (0);
}
