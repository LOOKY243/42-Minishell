/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:27 by ycostode          #+#    #+#             */
/*   Updated: 2024/02/16 16:48:25 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include "enum.h"
#include "struct.h"
#define BUFFER_SIZE 1024

extern bool exterminate;

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
int	ft_strncmp_case(const char *s1, const char *s2, size_t n);
int	ft_toupper(char c);

// SIGNAL
void	signal_handler(int signal);

// PRINT
int	print_strerror(char *str, int errnum, int value);
int	print_error(char *str, int value);
void	print(const char *s);
char	*prompt(char **envp);
void	modify_prompt(const char *s);
void	print_prompt(char *s);

// PIPE
void		close_file(int infile, int oufile);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split_cmd(char const *s, char c);
t_program		init_struct(t_cmd cmd, char **envp);
void		dups(int stdinfd, int stdoutfd);
void		close_fd(t_program program);
int    simple_exec(char **cmd, t_program program);
void	process(char *prompt, t_program *program);
void	wait_child(t_program program);

// BUILT-INS
int    	echo(char **cmd);
int		count_args(char	**arr);
char	*find_variable(char **envp, char *var);
int 	pwd(char **envp);
int 	env(char **envp);
void    ft_export(char **envp);
void    unset(t_program *program, char *s);
void exit_shell(char *s);
size_t len_until_sign(char  *str, int sign);
void    print_env(char  **envp);

// OTHERS
char	*random_string(t_program *program, int len);

#endif