/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/16 14:54:19 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_var_parsing(char **cmd, char **envp)
{
    int i;
    char    *var;

    i = 1;
    while (cmd[i] && ft_strcmp(cmd[i], '|'))
    {
        var = find_variable(envp, cmd[i]);
        if (var)
            print(var);
    }
}