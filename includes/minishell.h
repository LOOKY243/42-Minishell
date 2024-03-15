/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:19:27 by ycostode          #+#    #+#             */
/*   Updated: 2024/03/15 17:39:44 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "enum.h"
# include "struct.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# define BUFFER_SIZE 1024
# define MAX_TOKENS 20

extern bool	g_exterminate;

// LIBFT
size_t		ft_strlen(const char *str);
char		**ft_freesplit(char **split);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strdup(const char *s);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strncmp_case(const char *s1, const char *s2, size_t n);
int			ft_toupper(char c);
char		*ft_itoa(int n);
int			ft_isalpha(char *s);
char		*ft_strstr(const char *str, const char *to_find);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strjoin_mod(char const *s1, char const *s2);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_strchr(const char *s, int c);
int			ft_isalnum(int c);
int			ft_strlen_alnum(char *s);
bool		ft_atoi(const char *s, int *n);
void		*ft_memcpy(void *dest, const void *src, size_t n);

// SIGNAL
void		signal_c_handler(int signal);
void		signal_d_handler(int signal);
void		signal_slash_handler(int signal);

// PRINT
int			print_strerror(char *str, int errnum, int value);
int			print_error(char *str, int value);
void		print(const char *s);
void		print_fd(int fd, const char *s);
char		*prompt(char **envp);
void		modify_prompt(const char *s);
void		print_prompt(char *s);

// PIPE
void		close_file(int infile, int oufile);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split_cmd(char const *s, char c);
char		**ft_split(char const *s, char c);
t_program	init_struct(t_cmd cmd, char **envp);
void		dups(int stdinfd, int stdoutfd);
void		close_fd(t_program program);
int			simple_exec(char **cmd, t_program program);
void		process(char *prompt, t_program *program);
void		wait_child(t_program *program);
void		handle_file(t_program *program);
void		treat_child(t_program *program, char *cmd, int current, int max);
void		treat_child_recoded(t_program *program, char *cmd, int current,
				int max);
bool		is_recoded(char *cmd);

// PARSING
char		*treat_cmd(t_program program, char *cmd);
char		*change_cmd_var(t_program program, char *cmd);
void		remove_quote_split(int start, char **split);

// BUILT-INS
int			echo(char **cmd, int fd);
int			count_args(char **arr);
int			count_args_no_sign(char **arr);
char		*find_variable_secure(char **envp, char *var);
char		*find_variable(char **envp, char *var);
int			pwd(int fd);
int			env(char **envp, int fd);
int			export(t_program *program, char **var, int fd);
int			unset(t_program *program, char **strs);
void		exit_shell(t_program *program, char *s);
void		exit_shell2(t_program *program);
size_t		len_until_sign(char *str, int sign);
int			cd(t_program *program, char *path);
int			return_value(int value);

// OTHERS
char		*random_string(t_program *program, int len);
char		**custom_split(const char *input_string, int *count);
void		free_result(char **result, int count);
int			is_separator(char c);

#endif
