/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/16 16:55:29 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool exterminate = false;

void init_program(t_program *program, char **envp)
{
	program->envp = envp;
	program->path = ft_split_cmd(find_variable(envp, "PATH="), ':');
	program->exit_value = 0;
	program->infile = STDIN_FILENO;
	program->outfile = STDOUT_FILENO;
	program->random_file = NULL;
	program->pipe_saved = -1;
	program->rseed = 0;
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
	//signal(SIGINT, signal_handler);
	while (true) {
		exterminate = false;
		print_prompt(prompt(envp));
		s = readline("\x1b[1;30m╰─ \x1b[0m");
		if (!s)
			modify_prompt(s);
		if (s && *s)
		{
			exit_shell(s);
			modify_prompt(s);
			add_history(s);
			process(s, &program);
			free(s);
		}
		print("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}