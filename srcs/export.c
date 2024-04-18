/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:06:09 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 16:07:34 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_no_args(char **envp, int fd)
{
	int		i;
	int		j;
	char	**env;
	char	*tmp;

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

void	add_to_env_empty(char ***envp, char *line)
{
	char	**env;
	char	**new_env;
	int		i;

	if (is_in_env(*envp, line, ft_strlen(line)))
		return ;
	i = -1;
	env = *envp;
	new_env = ft_calloc(count_args_no_sign(env) + 2, sizeof(char *));
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = ft_strdup(line);
	++i;
	new_env[i] = NULL;
	ft_freesplit(env);
	*envp = new_env;
}

void	add_to_env(char ***envp, char *line, int index)
{
	char	**env;
	int		i;

	if (!is_in_env(*envp, line, index))
	{
		add_to_env_empty(envp, line);
		return ;
	}
	i = -1;
	env = *envp;
	while (env[++i])
	{
		if (ft_strncmp(env[i], line, index) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(line);
		}
	}
	++i;
	*envp = env;
}

int	export_var(t_program *program, char **var)
{
	int	i;
	int	index;

	if (program->cmd.len != 1)
		return (0);
	i = 0;
	while (var[++i])
	{
		index = ft_strchr(var[i], '=') - var[i];
		if (index <= 0)
			add_to_env_empty(&program->envp, var[i]);
		else if (var[i][index - 1] == '+')
			add_to_env_append(&program->envp, var[i], index - 1);
		else
			add_to_env(&program->envp, var[i], index);
	}
	return (0);
}

int	export(t_program *program, char **var, int fd)
{
	if (!program->envp || !program->envp[0])
		return (ENOENT);
	if (!var[1])
		return (export_no_args(program->envp, fd));
	return (export_var(program, var));
}
