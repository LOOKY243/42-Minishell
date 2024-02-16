/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/16 11:37:33 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	task(char *prompt, char **envp)
{
	char **cmd;
	pid_t pid;

	pid = fork();
	if (pid == 0) {
		cmd = ft_split_cmd(prompt, ' ');
		if (ft_strcmp(cmd[0], "echo") == 0 && ft_strcmp(cmd[1], "-n") == 0)
			echo(cmd);
		else if (ft_strcmp(cmd[0], "pwd") == 0)
			pwd(envp);
		else
			execve(cmd[0], cmd, envp);
		return ;
	}
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	char *s;

	if (argc != 1)
		return (print_fd(2, "\x1b[1;31mToo many args\n", EXIT_FAILURE));
	if (!envp || !envp[0])
		return (print_fd(2, "\x1b[1;31mNo environment\n", EXIT_FAILURE));
	signal(SIGINT, signal_handler);
	while (true) {
		print_prompt(prompt(envp));
		s = readline("\x1b[1;30m╰─ \x1b[0m");
		if (s && *s)
		{
			exit_shell(s);
			modify_prompt(s);
			add_history(s);
			//task(s, envp);
			free(s);
		}
	}
}