/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:03:50 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/09 15:25:08 by gmarre           ###   ########.fr       */
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

bool	check_n_arg(char *str)
{
	int	i;

	if (!str)
		return (false);
	if (str[0] != '-')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	echo(char **cmd, int fd)
{
	int	i;

	if (cmd[1] && check_n_arg(cmd[1]))
	{
		i = 2;
		while (check_n_arg(cmd[i]))
			i++;
		while (cmd[i] && ft_strcmp(cmd[i], "|"))
		{
			print_fd(fd, cmd[i]);
			if (i != count_args(cmd) - 1)
				print_fd(fd, " ");
			i++;
		}
		return (0);
	}
	i = 0;
	while (cmd[++i])
	{
		if (i != count_args(cmd))
			print_fd(fd, " ");
		print_fd(fd, cmd[i]);
	}
	printf("\n");
	return (0);
}
