/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:03:50 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/23 17:09:17 by gmarre           ###   ########.fr       */
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

int adjust_pointer(char **cmd)
{
	int i;

	i = 1;
	while (check_n_arg(cmd[i]))
		i++;
	return (i - 1);
}

int	echo(char **cmd, int fd)
{
	int	i;
	char *tmp;
	char *str;

	i = adjust_pointer(cmd);
	str = ft_calloc(1, sizeof(char));
	while (cmd[++i])
	{
		tmp = ft_strjoin(str, cmd[i]);
		free(str);
		str = tmp;
		if (cmd[i + 1])
		{
			tmp = ft_strjoin(str, " ");
			free(str);
			str = tmp;
		}
	}
	str = remove_quotes(tmp);
	print_fd(fd, str);
	if (!check_n_arg(cmd[1]))
		print_fd(fd, "\n");
	free(str);
	free(tmp);
	return (0);
}
