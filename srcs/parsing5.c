/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:12:43 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 16:13:30 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_double_quoted(char *str)
{
	if (str[0] == '\"')
	{
		if (str[ft_strlen(str) - 1] == '\"')
			return (1);
	}
	if (str[0] == '\'')
	{
		if (str[ft_strlen(str) - 1] == '\'')
			return (2);
	}
	return (0);
}

int	find_paired_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!quote && str[i] && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_command_sign(char *str)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	len = ft_strlen(str);
	quote = '\0';
	if (!str || !str[0])
		return (0);
	while (++i < len)
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = str[i];
		while (str[i] && quote != '\0')
		{
			i++;
			if (str[i] == quote)
				quote = '\0';
		}
		if (str[i] == '>' || str[i] == '<')
			return (1);
	}
	return (0);
}

char	*join_rest(char **cmds, int len)
{
	int		i;
	char	*res;
	char	*tmp;

	i = -1;
	res = NULL;
	while (++i < len)
	{
		if (cmds[i])
		{
			tmp = ft_strjoin_mod(res, cmds[i]);
			if (res)
				free(res);
			res = tmp;
		}
	}
	return (res);
}
