/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <ycostode@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/09 15:48:33 by ycostode         ###   ########.fr       */
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
		return (print_fd(2, "\033[1;31mToo many args\n", EXIT_FAILURE));
	if (!envp || !envp[0])
		return (print_fd(2, "\033[1;31mNo environment\n", EXIT_FAILURE));
	while (true) {
		s = readline("\033[1;37m$>\033[1;0m ");
		if (s && *s)
			add_history(s);
		task(s, envp);
		free(s);
	}
}