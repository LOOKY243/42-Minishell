/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/22 12:30:31 by gmarre           ###   ########.fr       */
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

void	read_stdin(t_program *program, char *limiter)
{
	int		is_quoted;
	char	*buffer;
	char	*tmp;

	if (program->infile)
		close(program->infile);
	program->random_file = random_string(program, 10);
	program->infile = open(program->random_file, O_CREAT | O_WRONLY | O_TRUNC,
			0666);
	is_quoted = is_double_quoted(limiter);
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
		else if (!ft_strncmp(buffer, &limiter[1], ft_strlen(&limiter[1]) - 1))
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

void	handle_file(t_program *program)
{
	char	**cut;
	int		len;
	int		trigger;
	int		i;
	int		j;

	j = -1;
	program->infile = STDIN_FILENO;
	program->outfile = STDOUT_FILENO;
	while (program->cmd.list[++j])
	{
		cut = custom_split(program->cmd.list[j], &len);
		i = -1;
		while (++i < len)
		{
			trigger = 1;
			if (is_command_sign(cut[i]) && is_command_sign(cut[i + 1]))
				return ;
			if (!ft_strcmp(cut[i], "<<"))
				read_stdin(program, cut[i + 1]);
			else if (!ft_strcmp(cut[i], ">>"))
				program->outfile = open(cut[i + 1],
						O_CREAT | O_WRONLY | O_APPEND, 0666);
			else if (!ft_strcmp(cut[i], "<"))
				program->infile = open(cut[i + 1], O_RDONLY);
			else if (!ft_strcmp(cut[i], ">") && cut[i + 1]
				&& !is_command_sign(cut[i + 1]))
				program->outfile = open(cut[i + 1],
						O_CREAT | O_WRONLY | O_TRUNC, 0666);
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
}
