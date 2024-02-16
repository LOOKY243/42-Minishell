/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:27 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/16 11:42:55 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "enum.h"
#include "struct.h"
#define BUFFER_SIZE 64

// LIBFT
size_t ft_strlen(const char *str);
char	**ft_freesplit(char **split);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);

// SIGNAL
void	signal_handler(int signal);

// PRINT
int	print_fd(int fd, char *str, int value);
int	print_error(char *str, int value);
void	print(const char *s);
char	*prompt(char **envp);
void	modify_prompt(const char *s);
void	print_prompt(char *s);

// PIPE
void		close_file(int infile, int oufile);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split_cmd(char const *s, char c);
t_pipex		init_struct(t_cmd cmd, char **envp);
void		dups(int stdinfd, int stdoutfd);
bool		treat_child(t_pipex *pipex, char *cmd, int current, int max);
void		close_fd(t_pipex pipex);

// BUILT-INS
int    echo(char **cmd);
char	*find_pwd(char **envp);
int pwd(char **envp);
void exit_shell(char *s);

#endif