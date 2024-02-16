/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:31:55 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/16 16:47:21 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_cmd
{
	char	**list;
	int		current;
	int		len;
}			t_cmd;

typedef struct s_program
{
	int		pipe[2];
	pid_t	pid[1024];
	t_cmd	cmd;
	int		infile;
	int		outfile;
	int		pipe_saved;
	char	*random_file;
	char	**path;
	char	**envp;
	int		exit_value;
	int		rseed;
}	t_program;

#endif