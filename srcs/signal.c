/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/03/13 16:45:43 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_c_handler(int signal)
{
	static bool shouldKill = true;
	(void)signal;

	if (!shouldKill)
	{
		shouldKill = !shouldKill;
		return ;
	}
	print("\n");
	kill(0, SIGINT);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	shouldKill = !shouldKill;
}
