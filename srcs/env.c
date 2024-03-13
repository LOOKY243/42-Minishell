/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:57:11 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/13 16:43:07 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **envp, int fd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] != '\0' && len_until_sign(envp[i],
				'=') != ft_strlen(envp[i]))
		{
			print_fd(fd, envp[i]);
			print_fd(fd, "\n");
		}
		i++;
	}
}

int	env(char **envp, int fd)
{
	if (!envp || !envp[0])
		return (ENOENT);
	print_env(envp, fd);
	return (0);
}
