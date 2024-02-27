/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:57:42 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/27 17:29:34 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(char *s)
{
    int i;

    if (!s || !s[0])
        return (0);
    i = 0;
    while (s[i])
    {
        if ((s[i] < 'a' && s[i] > 'z') && (s[i] < 'A' && s[i] > 'Z'))
            return (0);
        i++;
    }
    return (1);
}

char	*ft_strstr(const char *str, const char *to_find)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	j = 0;
	if (!to_find[j])
		return ((char *)str);
	while (str[i])
	{
		if (str[i] == to_find[j])
		{
			if (j == 0)
				index = i;
			j++;
		}
		else if (to_find[j] == 0)
			return ((char *)&str[index]);
		else
			j = 0;
		i++;
	}
	if (to_find[j] == 0)
		return ((char *)&str[index]);
	return (NULL);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	letter;

	letter = 0;
	while (src[letter])
	{
		dest[letter] = src[letter];
		letter++;
	}
	dest[letter] = '\0';
	return (dest);
}

char	*ft_strjoin_mod(char const *s1, char const *s2)
{
	char				*str;
	unsigned int		i;

	if (!s2)
		return (NULL);
	if (!s1)
		str = malloc(sizeof(char) * ft_strlen(s2) + 2);
	else
		str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = 0;
	if (s1)
		while (*s1)
			str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = ' ';
	i++;
	str[i] = 0;
	return (str);
}