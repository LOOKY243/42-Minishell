/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:46:29 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/28 17:13:27 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_countsplit(const char *s, char c)
{
	unsigned int	count;
	unsigned int	i;
	char			quote;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		count++;
		while (s[i] != c && s[i])
		{
			if (s[i] == '\'' || s[i] == '\"')
			{
				quote = s[i];
				i++;
				while (s[i] && s[i] != quote)
					i++;
				i++;
			}
			i++;
		}

	}
	return (count);
}

void	ft_prealloc2(char const *s, char quote, int *i, int *count)
{
	while (s[*i] && s[*i] != quote)
	{
		(*count)++;
		if (s[*i + 1] && (s[*i + 1] == '\'' || s[*i + 1] == '\"'))
			(*count)++;
		(*i)++;
	}
}

char	*ft_prealloc(char const *s, char c, int i)
{
	int	count;
	char	quote;

	count = 0;
	while (s[i] != c && s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			i++;
			count++;
			ft_prealloc2(s, quote, &i, &count);
			i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (ft_calloc((count + 1), sizeof(char)));
}

void	ft_split2(const char *s, char **strs, size_t i[3], char c)
{
	char	quote;
	
	while (s[i[0]] != c && s[i[0]])
	{
		if (s[i[0]] == '\'' || s[i[0]] == '\"')
		{
			quote = s[i[0]];
			strs[i[2]][i[1]++] = s[i[0]++];
			while (s[i[0]] && s[i[0]] != quote)
			{
				strs[i[2]][i[1]++] = s[i[0]++];
				if (s[i[0]] && s[i[0]] == quote)
				{
					strs[i[2]][i[1]] = s[i[0]];
					break;
				}
			}
			i[0]++;
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
	strs[i[2]] = 0;
	for (int k = 0; strs[k]; k++)
		printf("%d : %s\n", k, strs[k]);
	return (strs);
}
