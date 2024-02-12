/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:28:40 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/12 15:19:32 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((s1[i] < s2[i]) || (s2[i] < s1[i]))
			return (s1[i] - s2[i]);
		else
			i++;
	}
	return (0);
}

bool find_pipe(char **strs)
{
    int i;

    i = 0;
    while (strs[i])
    {
        if (!ft_strcmp(strs[i], "|"))
            return (true);
        i++;
    }
    return (false);
}
bool    parsing(char *cmd)
{
    char    **strs;

    strs = ft_split(cmd, ' ');

    // for (int i = 0; strs[i]; ++i)
    //     printf("%s\n", strs[i]);
    echo(strs);
    if (find_pipe(strs))
        return (true);
    return (false);
}