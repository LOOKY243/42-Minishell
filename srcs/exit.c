/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/16 11:37:33 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void destroy_program(t_program *program)
{
	ft_freesplit(program->envp);
	ft_freesplit(program->path);
	if (program->random_file)
		free(program->random_file);
}


void exit_shell(t_program *program, char *s)
{
	if (!ft_strcmp(s, "exit"))
	{
		modify_prompt(s);
		print("exit\n");
		free(s);
		destroy_program(program);
		exit(EXIT_SUCCESS);
	}
}