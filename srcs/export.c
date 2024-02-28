/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:06:09 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/27 18:24:08 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_export(char  **envp, int fd)
{
    int i;

    i = 0;
    while (envp[i])
    {
        if (envp[i][0] != '\0')
        {
            print_fd(fd, "declare -x ");
            print_fd(fd, envp[i]);
            print_fd(fd, "\n");
        }
        i++;
    }
}

char    **copy_arr(char **arr)
{
    int i;
    char    **copy;

    i = -1;
    copy = ft_calloc(count_args(arr) + 1, sizeof(char *));
    while (arr[++i])
        copy[i] = ft_strdup(arr[i]);
    copy[i] = NULL;
    return (copy);
}

int export_no_args(char **envp, int fd)
{
    int i;
    int j;
    char    **env;
    char    *tmp;

    env = copy_arr(envp);
    i = 0;
    while (env[i + 1])
    {
        j = i;
        while (env[++j])
        {
            if (ft_strcmp(env[i], env[j]) > 0)
            {
                tmp = env[i];
                env[i] = env[j];
                env[j] = tmp;
            }
        }
        i++;
    }
    print_export(env, fd);
    ft_freesplit(env);
    return (0);
}

void add_to_env(char ***envp, char *line)
{
    char    **env;
    char    **new_env;
    int i;

    i = -1;
    env = *envp;
    new_env = ft_calloc(count_args_no_sign(env) + 2, sizeof(char *));
    while (env[++i])
        new_env[i] = ft_strdup(env[i]);
    new_env[i] = ft_strdup(line);
    ++i;
    new_env[i] = NULL;
    ft_freesplit(env);
    // ft_freesplit(*envp);
    *envp = new_env;
}

int export_var(t_program *program, char **var)
{
    int i;

    i = 0;
    while (var[++i])
        add_to_env(&program->envp, var[i]);
    return (0);
}

int    export(t_program *program, char **var, int fd)
{
    if (!program->envp || !program->envp[0])
        return (ENOENT);
    if (!var[1])
        return (export_no_args(program->envp, fd));
    return (export_var(program, var));
}
