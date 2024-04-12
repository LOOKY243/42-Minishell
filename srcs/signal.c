/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/04/11 15:56:46 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_c_handler(int signal)
{
	static bool	should_kill = true;

	(void)signal;
	if (!should_kill)
	{
		should_kill = !should_kill;
		return ;
	}
	print("\n");
	kill(0, SIGINT);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	should_kill = !should_kill;
}
