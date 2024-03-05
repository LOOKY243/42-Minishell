/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:46:29 by ycostode          #+#    #+#             */
/*   Updated: 2024/03/05 17:45:24 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>

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
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		count++;
		while (s[i] != c && s[i])
		{
			if (s[i] == '\'')
				s_quote++;
			else if (s[i] == '\"')
				d_quote++;
			if (s[i] == '\'' || s[i] == '\"')
			{
				i++;
				while (s[i] && (d_quote % 2 || s_quote % 2))
				{
					if (s[i + 1] == '\'')
						s_quote++;
					else if (s[i + 1] == '\"')
						d_quote++;
					i++;
				}
			}
			i++;
		}
	}
	return (count);
}

void	ft_prealloc2(char const *s, int *d_quote, int *s_quote, int *i, int *count)
{
	while (s[*i] && (*d_quote % 2 || *s_quote % 2))
	{
		(*count)++;
		if (s[*i + 1] && (s[*i + 1] == '\'' || s[*i + 1] == '\"'))
		{
			if (s[*i + 1] == '\'')
				(*s_quote)++;
			else if (s[*i + 1] == '\"')
				(*d_quote)++;
			(*count)++;
		}
		(*i)++;
	}
}

char	*ft_prealloc(char const *s, char c, int i)
{
	int	count;
	int	s_quote;
	int	d_quote;

	count = 0;
	s_quote = 0;
	d_quote = 0;
	while (s[i] != c && s[i])
	{
		if (s[i] == '\'')
			s_quote++;
		else if (s[i] == '\"')
			d_quote++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			count++;
			ft_prealloc2(s, &d_quote, &s_quote, &i, &count);
		}
		else
		{
			count++;
			i++;
		}
	}
	return (calloc((count + 1), sizeof(char)));
}

void	ft_split2(const char *s, char **strs, size_t i[3], char c)
{
	int	s_quote = 0;
	int	d_quote = 0;
	
	while (s[i[0]] != c && s[i[0]])
	{
		if (s[i[0]] == '\'' || s[i[0]] == '\"')
		{
			strs[i[2]][i[1]++] = s[i[0]++];
			if (s[i[0] - 1] == '\'')
				s_quote++;
			else if (s[i[0] - 1] == '\"')
				d_quote++;
			while (s[i[0]] && ((s[i[0]] != '\'' && s[i[0]] != '\"') || (s[i[0]] == '\'' && s_quote % 2) || (s[i[0]] == '\"' && d_quote % 2)))
			{
				strs[i[2]][i[1]++] = s[i[0]++];
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
	strs = calloc(ft_countsplit(s, c) + 1, sizeof(char *));
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
