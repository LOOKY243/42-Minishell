/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:32:49 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/20 12:48:53 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_variable(char **envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
			return (&envp[i][ft_strlen(var)]);
		i++;
	}
	return (NULL);
}

int	pwd(char **envp)
{
	char	*pwd;

	pwd = find_variable(envp, "PWD=");
	if (!pwd)
		return (ENOENT);
	print(pwd);
	print("\n");
	return (0);
}
