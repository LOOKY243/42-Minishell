/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:32:49 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/05 12:58:37 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_variable_secure(char **envp, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && (envp[i][len] == '=' || envp[i][len] == '\0' || envp[i][len] == '\n'))
			return (&envp[i][ft_strlen(var)]);
		i++;
	}
	return (NULL);
}

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

int	pwd(int fd)
{
	char	pwd[BUFFER_SIZE];

	getcwd(pwd, sizeof(pwd));
	print_fd(fd, pwd);
	print_fd(fd, "\n");
	return (0);
}
