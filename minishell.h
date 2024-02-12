/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:06:06 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/12 15:17:47 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>

char    **ft_split(const char *s, char c);
void    *ft_calloc(size_t nmemb, size_t size);
bool    parsing(char *cmd);
int	    ft_strcmp(char *s1, char *s2);
bool    echo(char **cmd);

#endif