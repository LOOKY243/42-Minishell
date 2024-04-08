/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/04 16:46:10 by gmarre           ###   ########.fr       */
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

int find_paired_quotes(char *str)
{
	int i;
	char quote;

	i = 0;
	quote = 0;
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

char *remove_quotes(char *str)
{
	int 	i;
	int		j;
	char	quote;
	char	*copy;
	char	*new;

	if (!find_paired_quotes(str))
		return (ft_strdup(str));
	copy = ft_strdup(str);
	new = ft_calloc(1, sizeof(void));
	while (find_paired_quotes(copy))
	{
		i = 0;
		j = 0;
		quote = 0;
		free(new);
		new = ft_calloc(ft_strlen(str) - 1, sizeof(char));
		while (copy[i])
		{
			if (!quote && (str[i] == '\'' || str[i] == '\"'))
				quote = str[i++];
			if (str[i] == quote)
				i++;
			else
				new[j++] = str[i++];
		}
		free(copy);
		copy = ft_strdup(new);
	}
	free(copy);
	return (new);
}

void	read_stdin(t_program *program, char *limit)
{
	int		is_quoted;
	char	*buffer;
	char	*tmp;
	char	*limiter;

	if (program->infile)
		close(program->infile);
	program->random_file = random_string(program, 10);
	program->infile = open(program->random_file, O_CREAT | O_WRONLY | O_TRUNC,
			0666);
	is_quoted = is_double_quoted(limit);
	limiter = remove_quotes(limit);
	while (true)
	{
		buffer = readline("\x1b[0mheredoc> ");
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
		if (write(program->infile, tmp,
				ft_strlen(tmp)) != (int)ft_strlen(tmp))
		{
			print_error("write", EXIT_FAILURE);
			break ;
		}
		write(program->infile, "\n", 1);
		free(tmp);
	}
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
	if (!str)
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

int open_file(t_program *program, char *str, int type)
{
	int fd;

	if (!str)
	{
		if (program->cmd.current != program->cmd.len - 1)
			print_fd(2, "minishit: syntax error near unexpected token '|'\n");
		else
			print_fd(2, "minishit: syntax error near unexpected token 'newline'\n");
		return (-1);
	}
	if (type == 1)
		fd = open(str,
			O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (type == 2)
		fd = open(str, O_RDONLY);
	else
		fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
	{
		if (type == 1 || type == 3)
			perror("outfile");
		else
			perror("infile");
		return (-1);
	}
	if (type == 1 || type == 3)
		program->outfile = fd;
	else
		program->infile = fd;
	return (fd);
}

int	handle_file(t_program *program)
{
	char	**cut;
	int		len;
	int		trigger;
	int		i;
	int		j;

	j = -1;
	program->infile = STDIN_FILENO;
	program->outfile = STDOUT_FILENO;
	if (program->cmd.len == 0)
		print_fd(2, "minishit: syntax error near unexpected token '|'\n");
	while (program->cmd.list[++j])
	{
		cut = custom_split(program->cmd.list[j], &len);
		i = -1;
		while (++i < len)
		{
			trigger = 1;
			if (i == len - 1)
			{
				if (is_command_sign(cut[i]))
				{
					free_result(cut, len);
					print_fd(2, "minishit: syntax error near unexpected token 'newline'\n");
					return (0);
				}
			}
			else if (is_command_sign(cut[i]) && is_command_sign(cut[i + 1]))
			{
				if (j == program->cmd.len - 1)
					print_fd(2, "minishit: syntax error near unexpected token 'newline'\n");
				else
					print_fd(2, "minishit: syntax error near unexpected token '|'\n");
				free_result(cut, len);
				return (0);
			}
			if (!ft_strcmp(cut[i], "<<"))
				read_stdin(program, cut[i + 1]);
			else if (!ft_strcmp(cut[i], ">>"))
			{
				if (open_file(program, cut[i + 1], 1) == -1)
				{
					free_result(cut, len);
					return (0);
				}
			}
			else if (!ft_strcmp(cut[i], "<"))
			{
				if (i == len - 1)
				{
					print_fd(2, "minishit: syntax error near unexpected token 'newline'\n");
					free_result(cut, len);
					return (0);
				}
				if (open_file(program, cut[i + 1], 2) == -1)
				{
					free_result(cut, len);
					return (0);
				}
			}
			else if (!ft_strcmp(cut[i], ">"))
			{
				if (i == len - 1)
				{
					print_fd(2, "minishit: syntax error near unexpected token 'newline'\n");
					free_result(cut, len);
					return (0);
				}
				if (open_file(program, cut[i + 1], 3) == -1)
				{
					free_result(cut, len);
					return (0);
				}
			}
			else
				trigger = 0;
			if (trigger)
			{
				free(cut[i]);
				free(cut[i + 1]);
				cut[i] = 0;
				cut[i + 1] = 0;
			}
			if (program->random_file)
			{
				unlink(program->random_file);
				free(program->random_file);
			}
			program->random_file = 0;
		}
		free(program->cmd.list[j]);
		program->cmd.list[j] = join_rest(cut, len);
		free_result(cut, len);
	}
	return (1);
}
