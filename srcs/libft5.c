/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:49:12 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/01 14:49:16 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_inset(char c, const char *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	int		f;
	int		b;

	f = 0;
	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(s1) != 0)
		b = ft_strlen(s1) - 1;
	else
	{
		str = ft_calloc(1, sizeof(char));
		return (str);
	}
	while ((ft_inset(s1[f], set) != 0) || (ft_inset(s1[b], set) != 0))
	{
		if (ft_inset(s1[b], set) == 1)
			b--;
		if (ft_inset(s1[f], set) == 1)
			f++;
	}
	str = ft_substr(s1, f, b - f + 1);
	if (!str)
		return (NULL);
	return (str);
}
