/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/19 18:08:31 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_c_handler(int signal)
{
	(void)signal;
	print("^C\n");
	exterminate = true;
}

void	signal_d_handler(int signal)
{
	(void)signal;
	print("^D\n");
	exterminate = true;
}