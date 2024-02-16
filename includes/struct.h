/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycostode <ycostode@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:31:55 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/09 16:34:01 by ycostode         ###   ########.fr       */
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
typedef struct s_pipex
{
	int		pipe[2];
	t_cmd	cmd;
	int		infile;
	int		outfile;
	int		pipe_saved;
	char	**env;
	char	**envp;
	int		exit_value;
}			t_pipex;

#endif