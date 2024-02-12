/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:04:39 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/12 15:14:46 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (EXIT_FAILURE);
	(void)argv;
	(void)envp;
	int bytes;
	char	buff[BUFFER_SIZE];
	while (true)
	{
		write(STDERR_FILENO, "$", 1);
		bytes = read(STDIN_FILENO, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (EXIT_FAILURE);
		buff[bytes] = 0;
		if (parsing(buff))
		{
			printf("there is a pipe\n");
			// appel pipex
		}
		else
		{
			printf("no pipes in this command\n");
			// on fait un simple execve si la command n'est dans les commandes a recoder ?
			// else
			// cmd manager appelle la commande qu'on a recode
		}
	}
}