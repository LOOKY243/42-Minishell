/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <ycostode@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:40:49 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/09 16:42:20 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = (char *) ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, ft_strlen(s) + 1);
	return (ptr);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	int				nb;

	if (nmemb * size > INT32_MAX || (nmemb > UINT16_MAX && size > INT16_MAX))
		return (NULL);
	nb = nmemb * size;
	ptr = (unsigned char *) malloc(nb);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nb);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			*ptr;
	unsigned char	*ptr_last;

	ptr = (size_t *) s;
	while (n >= sizeof(size_t))
	{
		*ptr = 0;
		++ptr;
		n -= sizeof(size_t);
	}
	ptr_last = (unsigned char *) ptr;
	++n;
	while (--n)
	{
		*ptr_last = 0;
		++ptr_last;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = (char *) ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}