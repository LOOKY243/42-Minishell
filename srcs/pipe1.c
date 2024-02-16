/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:34 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/16 16:55:29 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dups(int stdinfd, int stdoutfd)
{
	if (stdinfd != STDIN_FILENO)
	{
		dup2(stdinfd, STDIN_FILENO);
		close(stdinfd);
	}
	if (stdoutfd != STDOUT_FILENO)
	{
		dup2(stdoutfd, STDOUT_FILENO);
		close(stdoutfd);
	}
}

void	close_file(int infile, int oufile)
{
	if (infile != -1)
	{
		perror("infile");
		close(infile);
	}
	if (oufile != -1)
	{
		perror("outfile");
		close(oufile);
	}
}

void	close_fd(t_program program)
{
	if (program.pipe_saved != -1)
		close(program.pipe_saved);
	close(program.infile);
	close(program.outfile);
}

void	wait_child(t_program program)
{
	int	i;

	i = program.cmd.len - 1;
	while (i >= 0)
		waitpid(program.pid[i--], NULL, 0);
}

static void	read_stdin(t_program *program, char *limiter)
{
	int		bytes;
	char	buffer[BUFFER_SIZE + 1];

	program->random_file = random_string(program, 10);
	program->infile = open(program->random_file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	bytes = 1;
	while (true)
	{
		if (bytes != 0)
			print("\x1b[0mheredoc> ");
		bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		buffer[bytes] = '\0';
		if (ft_strlen(buffer) - 1 == ft_strlen(limiter) && ft_strncmp(buffer,
				limiter, ft_strlen(limiter)) == 0)
			break ;
		if (write(program->infile, buffer, bytes) != bytes)
		{
			print_error("\x1b[1;6;31mwrite", EXIT_FAILURE);
			break ;
		}
	}
	close(program->infile);
	program->infile = open(program->random_file, O_RDONLY);
}

char	*get_cmds(t_program program, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	if (!cmd)
		return (NULL);
	if (!program.path)
		return (cmd);
	i = 0;
	while (program.path[i])
	{
		path = ft_strdup(program.path[i]);
		tmp = ft_strjoin(path, "/");
		free(path);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) != -1)
			return (path);
		free(path);
		++i;
	}
	return (cmd);
}

int	treat_command(t_program *program, char *cmd)
{
	char	**args;

	args = ft_split_cmd(cmd, ' ');
	if (ft_strcmp(args[0], "echo") == 0 && ft_strcmp(args[1], "-n") == 0)
		return (echo(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd(program->envp));
	if (ft_strcmp(args[0], "env") == 0)
		return (env(program->envp));
	if (ft_strcmp(args[0], "export") == 0 && !args[1])
	{
		ft_export(program->envp);
		return (0);
	}
	if (ft_strcmp(args[0], "$?") == 0)
	{
		printf("%d\n", program->exit_value);
		return (0);
	}
	// else if (ft_strcmp(cmd[0], "unset") == 0)
	// 	unset(program.envp, cmd[1]);
	args[0] = get_cmds(*program, args[0]);
	program->exit_value = 0;
	return (execve(args[0], args, program->envp));
}

void	treat_child(t_program *program, char *cmd, int current, int max)
{
	if (max != 0)
	{
		if (current == 0)
			dups(program->infile, program->pipe[PIPE_WRITE]);
		else if (current == max)
			dups(program->pipe_saved, program->outfile);
		else
			dups(program->pipe_saved, program->pipe[PIPE_WRITE]);
	}
	else
		dups(program->infile, program->outfile);
	close(program->pipe[PIPE_WRITE]);
	program->exit_value = treat_command(program, cmd);
	if (program->exit_value != 0)
	{
		close(program->pipe[PIPE_READ]);
		print_error("\x1b[1;6;31mexecve", program->exit_value);
	}
}

void	handle_file(char *prompt, t_program *program)
{
	char	**cut;
	int	i;

	cut = ft_split_cmd(prompt, ' ');
	i = -1;
	while (cut[++i]) {
		if (!ft_strcmp(cut[i], "<") && cut[i+ 1])
			program->infile = open(cut[i + 1], O_RDONLY);
		else if (!ft_strcmp(cut[i], ">") && cut[i+ 1])
			program->outfile = open(cut[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
		else if (!ft_strcmp(cut[i], "<<") && cut[i+ 1])
			read_stdin(program, cut[i + 1]);
		else if (!ft_strcmp(cut[i], ">>") && cut[i+ 1])
			program->outfile = open(cut[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	}
	ft_freesplit(cut);
}

int	exec(t_program *program, char *cmd)
{
	pid_t	pid;

	if (pipe(program->pipe) == -1)
		return (print_error("\x1b[1;6;31mpipe", EXIT_FAILURE));
	pid = fork();
	program->pid[program->cmd.current] = pid;
	if (pid == -1)
		return (print_error("\x1b[1;6;31mfork", EXIT_FAILURE));
	if (pid == 0)
	{
		treat_child(program, cmd, program->cmd.current, program->cmd.len - 1);
		exit(EXIT_SUCCESS);
	}
	if (program->pipe_saved != -1)
		close(program->pipe_saved);
	program->pipe_saved = program->pipe[PIPE_READ];
	close(program->pipe[PIPE_WRITE]);
	return (EXIT_SUCCESS);
}

int	size_list(char **list)
{
	int	i;

	if (!list)
		return (0);
	i = 0;
	while(list[i])
		++i;
	return (i);
}

void	process(char *prompt, t_program *program)
{
	program->cmd.current = 0;
	program->cmd.list = ft_split_cmd(prompt, '|');
	program->cmd.len = size_list(program->cmd.list);
	handle_file(prompt, program);
	if (program->infile == -1 || program->outfile == -1)
	{
		close_file(program->infile, program->outfile);
		ft_freesplit(program->cmd.list);
		return ;
	}
	while (program->cmd.list[program->cmd.current])
	{
		if (exec(program, program->cmd.list[program->cmd.current]))
			break ;
		program->cmd.current++;
	}
	if (program->random_file)
		unlink(program->random_file);
	program->random_file = NULL;
	close_fd(*program);
	ft_freesplit(program->cmd.list);
	wait_child(*program);
}