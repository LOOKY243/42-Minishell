/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:57:11 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/19 11:05:23 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_env(char  **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (envp[i][0] != '\0')
        {
            write(1, envp[i], ft_strlen(envp[i]));
            write(1, "\n", 1);
        }
        i++;
    }
}

int env(char **envp)
{
    print_env(envp);
    return (0);
}