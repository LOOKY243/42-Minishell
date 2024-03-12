/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/03/11 16:51:01 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_c_handler(int signal)
{
	(void)signal;
	print("^C\n");
}

void	signal_d_handler(int signal)
{
	(void)signal;
	print("exit\n");
	exterminate = true;
}

void signal_slash_handler(int signal)
{
    (void)signal;
}