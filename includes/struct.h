/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:31:55 by ycostode          #+#    #+#             */
/*   Updated: 2024/03/13 16:29:51 by ycostode         ###   ########.fr       */
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
	int		data_pipe[2];
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

#endif
