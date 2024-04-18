/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:10:21 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 16:12:00 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file2(int fd, int type)
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
