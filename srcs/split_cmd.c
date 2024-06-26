/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:46:29 by ycostode          #+#    #+#             */
/*   Updated: 2024/04/18 16:03:18 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_prealloc2(char const *s, int *d_quote, int *s_quote, int *i)
{
	int	count;

	count = 0;
	while (s[*i] && (*d_quote % 2 || *s_quote % 2))
	{
		count++;
		if (s[*i + 1] && (s[*i + 1] == '\'' || s[*i + 1] == '\"'))
		{
			if (s[*i + 1] == '\'')
				(*s_quote)++;
			else if (s[*i + 1] == '\"')
				(*d_quote)++;
			if (s[*i + 1] == '\'' || s[*i + 1] == '\"')
				(*i)++;
			count++;
		}
		(*i)++;
	}
	return (count);
}

char	*ft_prealloc(char const *s, char c, int i)
{
	int	count;
	int	s_quote;
	int	d_quote;

	count = 0;
	s_quote = 0;
	d_quote = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\'')
			s_quote++;
		else if (s[i] == '\"')
			d_quote++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			increase(&i, &count);
			count += ft_prealloc2(s, &d_quote, &s_quote, &i);
		}
		else
			increase(&i, &count);
	}
	return (ft_calloc((count + 1), sizeof(char)));
}

void	ft_split2(const char *s, char **strs, size_t i[3], char c)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (s[i[0]] != c && s[i[0]])
	{
		if (s[i[0]] == '\'' || s[i[0]] == '\"')
		{
			strs[i[2]][i[1]++] = s[i[0]];
			check_quote(s, i, &s_quote, &d_quote);
			while (s[++i[0]] && (s[i[0]] != '\'' && s[i[0]] != '\"')
				&& (s_quote % 2 || d_quote % 2))
			{
				check_quote(s, i, &s_quote, &d_quote);
				strs[i[2]][i[1]++] = s[i[0]];
			}
		}
		else
			strs[i[2]][i[1]++] = s[i[0]++];
	}
}

char	**ft_split_cmd(const char *s, char c)
{
	char	**strs;
	size_t	i[3];

	if (!s)
		return (NULL);
	strs = ft_calloc(ft_countsplit(s, c) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	i[2] = 0;
	i[0] = 0;
	while (s[i[0]])
	{
		while (s[i[0]] == c)
			i[0]++;
		if (!s[i[0]])
			break ;
		i[1] = 0;
		strs[i[2]] = ft_prealloc(s, c, i[0]);
		ft_split2(s, strs, i, c);
		i[2]++;
	}
	strs[i[2]] = NULL;
	return (strs);
}
