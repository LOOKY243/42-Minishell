/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:31:55 by ycostode          #+#    #+#             */
/*   Updated: 2024/03/15 16:29:44 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <fcntl.h>
# define MAX_FD 1024

typedef struct s_cmd
{
	char	**list;
	int		current;
	int		len;
}			t_cmd;

typedef struct s_program
{
	int		pipe[2];
	int		data_pipe[2];
	pid_t	pid[MAX_FD];
	t_cmd	cmd;
	int		infile;
	int		outfile;
	int		pipe_saved;
	char	*random_file;
	char	**envp;
	int		env_len;
	int		exit_value;
	int		rseed;
}			t_program;

typedef struct s_cmd_var
{
	char	*new_cmd;
	char	*tmp;
	char	*var_name;
	char	*env_value;
	int		i;
	int		start;
	int		end;
	int		len;
}			t_cmd_var;

#endif
