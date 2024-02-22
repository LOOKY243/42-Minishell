/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:38:01 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/16 14:10:26 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_toupper(char c)
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

static int	ft_size(int n)
{
	int	size;

	if (n <= 0)
		size = 1;
	else
		size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	int				length;
	int				sign;
	char			*num;

	if (n < 0)
		sign = -1;
	else
		sign = 1;
	nb = n * sign;
	length = ft_size(n);
	num = (char *) ft_calloc(length + 1, sizeof(char));
	if (!num)
		return (NULL);
	num[length--] = '\0';
	while (length >= 0)
	{
		num[length--] = nb % 10 + '0';
		nb /= 10;
	}
	if (sign == -1)
		num[0] = '-';
	return (num);
}