/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:24:41 by ycostode          #+#    #+#             */
/*   Updated: 2023/12/04 16:58:21 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	update_seed(t_program *program)
{
	program->rseed = program->rseed * 1103515245 + 12345;
	return ((program->rseed / 65536) % 32768);
}

int	random_number(t_program *program, int min, int max)
{
	int	range;
	int	rand;

	if (min > max)
		return (-1);
	range = max - min + 1;
	rand = update_seed(program) % range + min;
	return (rand);
}

char	*random_string(t_program *program, int len)
{
	char *name;
	char	*usable;
	int	i;

	usable = "abcdefghijklmnopqrstuvwxyz";
	while (true)
	{
		name = ft_calloc(len + 1, sizeof(char));
		i = -1;
		while (++i < len)
			name[i] = usable[random_number(program, 0, ft_strlen(usable))];
		name[len] = '\0';
		if (access(name, F_OK) == -1)
			break;
		free(name);
	}
	return (name);
}