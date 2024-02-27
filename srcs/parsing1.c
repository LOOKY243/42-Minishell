/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/27 18:19:13 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_next_sign(char *str, char *sign)
{
    int i;
    char    **strs;

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
    char    **cut;
    char	*tmp;
    int	i;

    i = 0;
    if (index == i)
        i = 2;
    tmp = NULL;
    cut = ft_split(cmd, ' ');
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
    ft_freesplit(cut);
    return (line);
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

int is_command_sign(char *str)
{
    int i;

    i = -1;
    if (!str)
        return (0);
    while (str[++i])
    {
        if (str[i] == '>' || str[i] == '<')
            return (1);
    }
    return (0);
}

char    *join_rest(char **cmds, int len)
{
    int i;
    char    *res;
    char    *tmp;

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
    int     len;
    int	i;
    int	j;

    j = -1;
    program->infile = STDIN_FILENO;
    program->outfile = STDOUT_FILENO;
    while (program->cmd.list[++j])
    {
        cut = custom_split(program->cmd.list[j], &len);
        i = -1;
        while (++i < len)
        {
            if (is_command_sign(cut[i]) && is_command_sign(cut[i + 1]))
                return ;
            if (!ft_strcmp(cut[i], "<<"))
            {
                read_stdin(program, cut[i + 1]);
                free(cut[i]);
                free(cut[i + 1]);
                cut[i] = 0;
                cut[i + 1] = 0;
            }
            else if (!ft_strcmp(cut[i], ">>"))
            {
                program->outfile = open(cut[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
                free(cut[i]);
                free(cut[i + 1]);
                cut[i] = 0;
                cut[i + 1] = 0;
            }
            else if (!ft_strcmp(cut[i], "<"))
            {
                program->infile = open(cut[i + 1], O_RDONLY);
                free(cut[i]);
                free(cut[i + 1]);
                cut[i] = 0;
                cut[i + 1] = 0;
            }
            else if (!ft_strcmp(cut[i], ">") && cut[i + 1] && !is_command_sign(cut[i + 1]))
            {
                program->outfile = open(cut[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
                free(cut[i]);
                free(cut[i + 1]);
                cut[i] = 0;
                cut[i + 1] = 0;
            }
            if (program->random_file)
                unlink(program->random_file);
            program->random_file = 0;
        }
        program->cmd.list[j] = join_rest(cut, len);
        free_result(cut, len);
    }
}
