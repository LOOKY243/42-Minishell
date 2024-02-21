/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:24:46 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/21 14:28:39 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *change_oldpwd(char *envp, char *pwd)
{
    char    *new;

    new = ft_strjoin("OLDPWD=", pwd);
    free(envp);
    return (new);
}

int    cd(char **envp, char *path)
{
    int     i;
    char    *pwd;
    
    if (path[0] == '-' && ft_strlen(path) == 1)
        path = find_variable(envp, "OLDPWD=");
    if (chdir(path) != 0)
    {
        perror("chdir");
        return (-1);
    }
    pwd = find_variable(envp, "PWD=");
    i = 0;
    while (ft_strncmp("OLDPWD=", envp[i], 7))
        i++;
    envp[i] = change_oldpwd(envp[i], pwd);
    i = 0;
    while (ft_strncmp("PWD=", envp[i], 4))
        i++;
    free(envp[i]);
    envp[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
    return (0);
}
