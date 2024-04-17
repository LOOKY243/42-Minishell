/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/17 15:05:25 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next_sign(char *str, char *sign)
{
	int		i;
	char	**strs;

	i = 0;
	strs = ft_split(str, ' ');
	while (strs[i] && ft_strncmp(strs[i], sign, ft_strlen(sign) - 1))
		i++;
	ft_freesplit(strs);
	return (i);
}

char	*cmd_trim(char *cmd, int index)
{
	char	*line;
	char	**cut;
	char	*tmp;
	int		i;

	i = 0;
	if (index == i)
		i = 2;
	tmp = NULL;
	cut = ft_split(cmd, ' ');
	line = ft_strdup(cut[i]);
	while (cut[++i])
	{
		if (i != index && i != index + 1)
		{
			tmp = ft_strjoin(line, " ");
			free(line);
			line = ft_strjoin(tmp, cut[i]);
			free(tmp);
		}
	}
	free(cmd);
	ft_freesplit(cut);
	return (line);
}

int	is_double_quoted(char *str)
{
	if (str[0] == '\"')
	{
		if (str[ft_strlen(str) - 1] == '\"')
			return (1);
	}
	if (str[0] == '\'')
	{
		if (str[ft_strlen(str) - 1] == '\'')
			return (2);
	}
	return (0);
}

int	find_paired_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!quote && str[i] && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*new;

	if (!find_paired_quotes(str))
		return (ft_strdup(str));
	new = ft_calloc(ft_strlen(str) - 1, sizeof(char));
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i++];
		if (str[i] == quote)
		{
			i++;
			quote = 0;
		}
		else
			new[j++] = str[i++];
	}
	return (new);
}

void	sigint_handler(int signal)
{
	(void)signal;
	write(0, "\n", 1);
	g_exterminate = 1;
}

int read_stdin3(t_program *program, char *tmp)
{
	if (write(program->infile, tmp, ft_strlen(tmp)) != (int)ft_strlen(tmp))
	{
		print_error("write", EXIT_FAILURE);
		return (0);
	}
	write(program->infile, "\n", 1);
	free(tmp);
	return (1);
}

int read_stdin2_bis(char *buffer)
{
	if (buffer == NULL)
	{
		print_fd(STDOUT_FILENO,
			"minishit: warning: here-document \
at line 3 delimited by end-of-file (wanted 'eof')\n");
		return (0);
	}
	return (1);
}

void read_stdin2(t_program *program, char *limit, char *limiter, int is_quoted)
{
	char *tmp;
	char *buffer;
	
	while (g_exterminate != 1)
	{
		buffer = readline("\x1b[0mheredoc> ");
		if (!read_stdin2_bis(buffer))
			break ;
		if (!is_quoted)
		{
			tmp = change_cmd_var(*program, buffer);
			if (!ft_strcmp(buffer, limiter))
			{
				free(tmp);
				break ;
			}
		}
		else if (!ft_strncmp(buffer, &limit[1], ft_strlen(&limit[1]) - 1))
			break ;
		else
			tmp = ft_strdup(buffer);
		if (!read_stdin3(program, tmp))
			break ;
	}
}

void	read_stdin(t_program *program, char *limit)
{
	int		is_quoted;
	char	*limiter;

	signal(SIGINT, sigint_handler);
	if (program->infile)
		close(program->infile);
	if (!strcmp(limit, ""))
		return ;
	program->random_file = random_string(program, 10);
	program->infile = open(program->random_file, O_CREAT | O_WRONLY | O_TRUNC,
			0666);
	is_quoted = is_double_quoted(limit);
	limiter = remove_quotes(limit);
	read_stdin2(program, limit, limiter, is_quoted);
	close(program->infile);
	program->infile = open(program->random_file, O_RDONLY);
	free(limiter);
}

int	is_command_sign(char *str)
{
	int		i;
	char	quote;

	i = -1;
	quote = '\0';
	if (!str || !str[0])
		return (0);
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = str[i];
		while (str[i] && quote != '\0')
		{
			i++;
			if (str[i] == quote)
				quote = '\0';
		}
		if (str[i] == '>' || str[i] == '<')
			return (1);
	}
	return (0);
}

char	*join_rest(char **cmds, int len)
{
	int		i;
	char	*res;
	char	*tmp;

	i = -1;
	res = NULL;
	while (++i < len)
	{
		if (cmds[i])
		{
			tmp = ft_strjoin_mod(res, cmds[i]);
			if (res)
				free(res);
			res = tmp;
		}
	}
	return (res);
}

int open_file2(int fd, int type)
{
	if (fd == -1)
	{
		if (type == 1 || type == 3)
			perror("outfile");
		else
			perror("infile");
		return (1);
	}
	return (0);
}

int	open_file(t_program *program, char *str, int type)
{
	int	fd;

	if (!str)
	{
		if (program->cmd.current != program->cmd.len - 1)
			print_fd(2, "minishit: syntax error near unexpected token '|'\n");
		else
			print_fd(2,
				"minishit: syntax error near unexpected token 'newline'\n");
		return (-1);
	}
	if (type == 1)
		fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (type == 2)
		fd = open(str, O_RDONLY);
	else
		fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (open_file2(fd, type))
		return (-1);
	if (type == 1 || type == 3)
		program->outfile = fd;
	else
		program->infile = fd;
	return (fd);
}
