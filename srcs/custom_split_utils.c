/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:04:31 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 16:05:44 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_char(char c, char next)
{
	return (c == ' ' || c == '<' || c == '>' || (c == ' ' && (next == '<'
				|| next == '>')));
}

void	free_result(char **result, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		free(result[i]);
	free(result);
}
