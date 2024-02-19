/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:24:46 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/19 10:46:04 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cd(char  **envp, char *cd)
{
    size_t i;

    i = 0;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], "PWD=", 4))
        {
            if (cd[0] == '/')
                envp[i] = cd;
        }
        i++;
    }
}