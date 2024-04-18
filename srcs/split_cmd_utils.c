/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:02:30 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 16:05:54 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increase(int *i, int *count)
{
	(*i)++;
	(*count)++;
}

void	check_quote(const char *s, size_t i[3], int *s_quote, int *d_quote)
{
	if (s[i[0]] == '\'')
		(*s_quote)++;
	else if (s[i[0]] == '\"')
		(*d_quote)++;
}

void	ft_countsplit2(const char *s, unsigned int *i, unsigned int *d_quote,
		unsigned int *s_quote)
{
	if (s[*i] == '\'')
		(*s_quote)++;
	else if (s[*i] == '\"')
		(*d_quote)++;
	if (s[*i] == '\'' || s[*i] == '\"')
	{
		(*i)++;
		while (s[*i] != '\0' && ((*d_quote) % 2 || (*s_quote) % 2))
		{
			if (s[*i] == '\'')
				(*s_quote)++;
			else if (s[*i] == '\"')
				(*d_quote)++;
			(*i)++;
		}
	}
	else if (s[*i] != '\0')
		(*i)++;
}

unsigned int	ft_countsplit(const char *s, char c)
{
	unsigned int	count;
	unsigned int	i;
	unsigned int	d_quote;
	unsigned int	s_quote;

	count = 0;
	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		count++;
		while (s[i] != c && s[i] != '\0')
		{
			ft_countsplit2(s, &i, &d_quote, &s_quote);
		}
	}
	return (count);
}
