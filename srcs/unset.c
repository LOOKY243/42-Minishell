/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:46:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/19 16:38:40 by gmarre           ###   ########.fr       */
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

void    unset(t_program *program, char *s)
{
    size_t i;
    
    i = 0;
    while (program->envp[i])
    {
        if (!ft_strncmp_case(program->envp[i], s, ft_strlen(s)) && len_until_sign(program->envp[i], '=') == ft_strlen(s))
        {
            free(program->envp[i]);
            program->envp[i] = ft_strdup("\0");
            break ;
        }
        i++;
    }
}
