/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:38:01 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/16 17:41:50 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] - str2[i] != 0)
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp_case(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] - str2[i] != 0 && ft_toupper(str1[i]) != str2[i]
			&& ft_toupper(str2[i]) != str1[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}