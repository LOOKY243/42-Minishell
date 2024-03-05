/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:24:46 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/05 15:50:02 by gmarre           ###   ########.fr       */
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

void     cd_loop(t_program *program)
{
    int i;

    i = 0;
    while (program->envp[i] && ft_strncmp("PWD=", program->envp[i], 4))
        i++;
    if (program->envp[i])
    {
        free(program->envp[i]);
        program->envp[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
    }
}

int     cd(t_program *program, char *path)
{
    int     i;
    char    pwd[BUFFER_SIZE];

    if (program->cmd.len != 1)
        return (0);
    if (path[0] == '-' && ft_strlen(path) == 1)
        path = find_variable(program->envp, "OLDPWD=");
    if (!path)
        return (ENOENT);
    getcwd(pwd, sizeof(pwd));
    if (chdir(path) != 0)
    {
        perror("chdir");
        return (ENOENT);
    }
    i = 0;
    while (program->envp[i] && ft_strncmp("OLDPWD=", program->envp[i], 7))
        i++;
    if (program->envp[i])
        program->envp[i] = change_oldpwd(program->envp[i], pwd);
    cd_loop(program);
    return (0);
}
