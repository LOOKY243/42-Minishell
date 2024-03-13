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
	(void)signal;

	print("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_d_handler(int signal)
{
	(void)signal;
	print("exit\n");
	g_exterminate = true;
}

void	signal_slash_handler(int signal)
{
	(void)signal;
}
