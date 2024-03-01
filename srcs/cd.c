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

int    cd(t_program *program, char *path)
{
    int     i;
    char    *pwd;

    if (program->cmd.len != 1)
        return (0);
    if (path[0] == '-' && ft_strlen(path) == 1)
        path = find_variable(program->envp, "OLDPWD=");
    if (chdir(path) != 0)
    {
        perror("chdir");
        return (ENOENT);
    }
    pwd = find_variable(program->envp, "PWD=");
    i = 0;
    while (ft_strncmp("OLDPWD=", program->envp[i], 7))
        i++;
    program->envp[i] = change_oldpwd(program->envp[i], pwd);
    i = 0;
    while (ft_strncmp("PWD=", program->envp[i], 4))
        i++;
    free(program->envp[i]);
    program->envp[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
    return (0);
}
