/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/03/13 16:43:15 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_value(int value)
{
	printf("%d\n", value);
	return (0);
}

void	destroy_program(t_program *program)
{
	ft_freesplit(program->envp);
	if (program->random_file)
		free(program->random_file);
}

void	exit_shell(t_program *program, char *s)
{
	int		n;
	char	**split;

	print("exit\n");
	split = ft_split_cmd(s, ' ');
	if (!split || !split[0] || !split[1])
	{
		ft_freesplit(split);
		free(s);
		destroy_program(program);
		exit(program->exit_value);
	}
	if (!ft_atoi(split[1], &n))
	{
		ft_freesplit(split);
		print_fd(2, "\x1b[1;31mexit: numeric argument required\n\x1b[0m");
		free(s);
		destroy_program(program);
		exit(2);
	}
	if (split[1] && split[2])
	{
		program->exit_value = 1;
		return (print_fd(2, "\x1b[1;31mexit: too many arguments\n\x1b[0m"));
	}
	ft_freesplit(split);
	free(s);
	destroy_program(program);
	exit(n);
}

void	exit_shell2(t_program *program)
{
	print("exit\n");
	destroy_program(program);
	exit(2);
}
