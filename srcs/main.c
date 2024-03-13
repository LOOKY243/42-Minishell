/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/03/12 14:49:59 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool exterminate = false;

char	**copy_envp(char **envp)
{
	int	i;
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

void init_program(t_program *program, char **envp)
{
	program->envp = copy_envp(envp);
	program->random_file = NULL;
	program->rseed = 0;
	program->exit_value = 0;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	char *s;
	t_program program;

	if (argc != 1)
		return (print_strerror("minishell: ", E2BIG, EXIT_FAILURE));
	if (!envp || !envp[0])
		return (print_strerror("env: ", ENODATA, EXIT_FAILURE));
	init_program(&program, envp);
	print("\x1b[1;34mEarly Access v0.1\n\x1b[0m");
	signal(SIGINT, signal_c_handler);
	signal(SIGQUIT, signal_d_handler);
	signal(SIGQUIT, signal_slash_handler);
	while (true)
	{
		exterminate = false;
		print_prompt(prompt(program.envp));
		s = readline("\x1b[1;30m╰─ \x1b[0m");
		if (!s || ft_strlen(s) == 0)
			exit_shell(&program, s);
		else if (*s)
		{
			add_history(s);
			modify_prompt(s);
			if (!ft_strncmp(s, "exit", 4) && (s[4] == '\0' || s[4] == ' '))
				exit_shell(&program, s);
			else
				process(s, &program);
			free(s);
		}
		print("\n");
	}
}