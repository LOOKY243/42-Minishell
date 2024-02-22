/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/16 14:54:19 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_trim(char *cmd, char **cut, int index)
{
    char	*line;
    char	*tmp;
    int	i;

    i = 0;
    tmp = NULL;
    line = ft_strdup(cut[i]);
    while(cut[++i]) {
        if (i != index && i != index + 1)
        {
            tmp = ft_strjoin(line, " ");
            free(line);
            line = ft_strjoin(tmp, cut[i]);
            free(tmp);
        }
    }
    free(cmd);
    cmd = ft_strdup(line);
}

void	read_stdin(t_program *program, char *limiter)
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

void	handle_file(t_program *program)
{
    char	**cut;
    int	i;
    int	j;

    j = -1;
    program->infile = STDIN_FILENO;
    program->outfile = STDOUT_FILENO;
    while (program->cmd.list[++j])
    {
        cut = ft_split_cmd(program->cmd.list[j], ' ');
        i = -1;
        while (cut[++i]) {
            if (!ft_strcmp(cut[i], "<") && cut[i + 1]) {
                program->infile = open(cut[i + 1], O_RDONLY);
                cmd_trim(program->cmd.list[j], cut, i);
            }
            else if (!ft_strcmp(cut[i], ">") && cut[i+ 1]) {
                program->outfile = open(cut[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
                cmd_trim(program->cmd.list[j], cut, i);
            }
            else if (!ft_strcmp(cut[i], "<<") && cut[i+ 1]) {
                read_stdin(program, cut[i + 1]);
                cmd_trim(program->cmd.list[j], cut, i);
            }
            else if (!ft_strcmp(cut[i], ">>") && cut[i+ 1]) {
                program->outfile = open(cut[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
                cmd_trim(program->cmd.list[j], cut, i);
            }
        }
        ft_freesplit(cut);
    }
}