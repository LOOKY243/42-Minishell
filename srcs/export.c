/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:06:09 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/20 11:44:46 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_copy(char  **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void    print_export(char  **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (envp[i][0] != '\0')
            printf("%d declare -x %s\n", i, envp[i]);
        i++;
    }
}

char    **copy_arr(char **arr)
{
    int i;
    char    **copy;

    i = -1;
    copy = ft_calloc(count_args(arr) + 1, sizeof(char *));
    while (arr[++i])
        copy[i] = ft_strdup(arr[i]);
    copy[i] = NULL;
    return (copy);
}

void    ft_export(char **env)
{
    int i;
    int j;
    char    **envp;
    char    *tmp;
    
    envp = copy_arr(env);
    i = 0;
    while (envp[i + 1])
    {
        j = i;
        while (envp[++j])
        {
            if (ft_strcmp(envp[i], envp[j]) > 0)
            {
                tmp = envp[i];
                envp[i] = envp[j];
                envp[j] = tmp;
            }
        }
        i++;
    }
    print_export(envp);
    free_copy(envp);
}
