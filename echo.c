/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:03:50 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/12 15:59:34 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    echo(char **cmd)
{
    int	i;

    if (ft_strcmp(cmd[0], "echo") || ft_strcmp(cmd[1], "-n"))
        return (false);
    i = 2;
	while (cmd[i] && ft_strcmp(cmd[i], "|"))
	{
		if (cmd[i + 1])
			printf("%s ", cmd[i]);
		else
			printf("%s", cmd[i]);
		i++;
	}
	return (true);
}