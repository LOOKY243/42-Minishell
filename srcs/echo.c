/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:03:50 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/16 16:11:43 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i] && ft_strcmp(arr[i], "|"))
		i++;
	return (i);
}

int	count_args_no_sign(char	**arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int    echo(char **cmd)
{
    int	i;

    i = 2;
	while (cmd[i] && ft_strcmp(cmd[i], "|"))
	{
		print(cmd[i]);
		if (i != count_args(cmd) - 1)
			print(" ");
		i++;
	}
	return (0);
}
