/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/04/23 17:13:40 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_envp(char **envp)
{
	int		i;
	char	**env;

	env = ft_calloc(count_args(envp) + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = 0;
	return (env);
}

void	init_program(t_program *program, char **envp)
{
	program->envp = copy_envp(envp);
	program->random_file = NULL;
	program->rseed = 0;
	program->exit_value = 0;
}

void	main_conditions(char *s, t_program *program)
{
	if (!s)
	{
		modify_prompt(s);
		exit_shell(program, s);
	}
	else if (ft_strlen(s) == 0)
	{
		modify_prompt(s);
		free(s);
	}
	else if (*s)
	{
		add_history(s);
		modify_prompt(s);
		if (!ft_strncmp(s, "exit", 4) && (s[4] == '\0' || s[4] == ' '))
			exit_shell(program, s);
		else
			process(s, program);
		free(s);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*s;
	t_program	program;

	(void)argv;
	if (argc != 1)
		return (print_strerror("args", E2BIG, EXIT_FAILURE));
	if (!envp || !envp[0])
		return (print_strerror("env", ENODATA, EXIT_FAILURE));
	init_program(&program, envp);
	print("\x1b[1;34mEarly Access v0.1\n\x1b[0m");
	signal(SIGINT, signal_c_handler);
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		print_prompt(prompt(program.envp));
		s = readline("\x1b[1;30m╰─ \x1b[0m");
		main_conditions(s, &program);
		print("\n");
	}
}
