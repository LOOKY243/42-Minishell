/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:24:46 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/19 16:23:55 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cd(char  **envp, char *cd)
{
    size_t i;
    char    *tmp;

    i = 0;
    while (ft_strncmp(envp[i], "PWD=", 4)                                    )
        i++;
    if (cd[0] == '/')
    {
        tmp = ft_strjoin("PWD=", cd);
        free(envp[i]);
        envp[i] = tmp;
    }

}