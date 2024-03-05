/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/01 12:24:37 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*treat_cmd(t_program program, char *cmd)
{
	char *tmp;
	char *final;

	tmp = remove_quote(cmd);
	final = change_cmd_var(program, tmp);
	return (final);
}

char	*remove_quote(char *str)
{
	int i;
	int offset;
	char *tmp;
	char *final;
	char quote;

	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = -1;
	offset = 0;
	quote = 0;
	while (str[++i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
		{
			quote = str[i];
			++offset;
			continue;
		}
		if (quote == str[i])
		{
			quote = 0;
			++offset;
			continue;
		}
		tmp[i - offset] = str[i];
	}
	tmp[i - offset] = '\0';
	final = ft_strdup(tmp);
	free(tmp);
	return (final);
}