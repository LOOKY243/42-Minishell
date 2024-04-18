/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:58:02 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 15:59:19 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(char *s)
{
	int	i;
	int	index;

	i = -1;
	index = -1;
	while (s[++i])
	{
		if (s[i] == '/')
			index = i;
	}
	printf("%.*s", index + 1, s);
	printf("\x1b[1;34m%s", &s[index + 1]);
	free(s);
}

void	modify_prompt(const char *s)
{
	print("\x1b[1A\x1b[0K");
	print("\x1b[1A\x1b[0K");
	print("\x1b[1A\x1b[0K");
	print("\x1b[1;33m❯\x1b[0m ");
	print(s);
	print("\n");
}
