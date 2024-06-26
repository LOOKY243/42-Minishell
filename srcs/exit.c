/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/04/10 13:26:31 by gmarre           ###   ########.fr       */
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

void	check_split_arg(char **split, t_program *program, long long *n, char *s)
{
	if (!ft_atoi(split[1], n))
	{
		ft_freesplit(split);
		print_fd(2, "\x1b[1;31mexit: numeric argument required\n\x1b[0m");
		free(s);
		destroy_program(program);
		exit(2);
	}
}

void	exit_shell(t_program *program, char *s)
{
	long long	n;
	char		**split;

	print("exit\n");
	split = ft_split_cmd(s, ' ');
	if (!split || !split[0] || !split[1])
	{
		ft_freesplit(split);
		free(s);
		destroy_program(program);
		exit(program->exit_value % 256);
	}
	check_split_arg(split, program, &n, s);
	if (split[1] && split[2])
	{
		program->exit_value = 1;
		return (print_fd(2, "\x1b[1;31mexit: too many arguments\n\x1b[0m"));
	}
	ft_freesplit(split);
	free(s);
	destroy_program(program);
	exit(n % 256);
}

void	free_child(t_program *program, char *new_cmd)
{
	ft_freesplit(program->cmd.list);
	ft_freesplit(program->envp);
	free(new_cmd);
	return ;
}
