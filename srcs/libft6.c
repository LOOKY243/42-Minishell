/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:56 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/11 13:01:51 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*char_dest;
	unsigned const char	*char_src;
	unsigned int		i;

	if (!src && !dest)
		return (NULL);
	char_dest = (unsigned char *)dest;
	char_src = (unsigned const char *)src;
	i = 0;
	while (i < n)
	{
		char_dest[i] = char_src[i];
		i++;
	}
	return (dest);
}

bool	ft_atoi(const char *s, long long *n)
{
	int					i;
	int					sign;
	unsigned long long	tmp;

	i = 0;
	*n = 0;
	tmp = 0;
	sign = 1;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '+' || s[i] == '-')
		++i;
	while (s[i] == '0')
		++i;
	if (ft_strlen(&s[i]) > 19 || (ft_strlen(&s[i]) == 0 && s[i - 1] != '0'))
		return (false);
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (false);
		tmp = tmp * 10 + (s[i] - '0');
		++i;
	}
	if ((sign == 1 && tmp > LLONG_MAX) || (sign == -1 && tmp - 1 > LLONG_MAX))
		return (false);
	*n = tmp * sign;
	return (true);
}

int	is_separator(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (0);
	return (1);
}
