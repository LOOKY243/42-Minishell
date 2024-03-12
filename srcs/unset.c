/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:46:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/11 17:19:49 by gmarre           ###   ########.fr       */
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

int    unset(t_program *program, char **strs)
{
    size_t i;
    size_t j;


    if (program->cmd.len != 1)
        return (0);
    j = 0;
    while (strs[j] && ft_strncmp(strs[j], "|", 1))
    {
        i = 0;
        while (program->envp[i])
        {
            if (!ft_strncmp(program->envp[i], strs[j], ft_strlen(strs[j])) && len_until_sign(program->envp[i], '=') == ft_strlen(strs[j]))
            {
                free(program->envp[i]);
                program->envp[i] = ft_strdup("\0");
                break ;
            }
            i++;
        }
        j++;
    }
    return (0);
}
