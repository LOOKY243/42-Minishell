/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:46:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/19 11:25:49 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t len_until_sign(char  *str, int sign)
{
    size_t i;
    
    if (!str)
        return (0);
    i = 0;
    while (str[i] && str[i] != sign)
        i++;
    return (i);
}

void    free_envp(char  **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}

char    **new_envp(char **envp, int to_avoid)
{
    char    **env;
    int     i;
    int     j;

    env = ft_calloc(count_args(envp) - 1, sizeof(char *));
    if (!env)
        return (NULL);
    i = 0;
    j = 0;
    while (envp[i])
    {
        if (i == to_avoid)
            j++;
        env[i + j] = ft_strdup(envp[i]);
        i++;
    }
    env[i + j] = 0;
    return (env);
}

void    unset(t_program *program, char *s)
{
    static int  j = 0;
    size_t i;
    int     var;

    i = 0;
    var = 0;
    while (program->envp[i])
    {
        if (!ft_strncmp_case(program->envp[i], s, ft_strlen(s)) && len_until_sign(program->envp[i], '=') == ft_strlen(s))
        {
            var = i;
            break ;
        }
        i++;
    }
    if (j)
        free_envp(program->envp);
    j++;
    if (var)
        program->envp = new_envp(program->envp, var);
}
