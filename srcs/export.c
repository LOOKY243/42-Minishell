/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:06:09 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/12 14:26:52 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **envp, int fd)
{
	int	i;

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

char	**copy_arr(char **arr)
{
	int		i;
	char	**copy;

	i = -1;
	copy = ft_calloc(count_args(arr) + 1, sizeof(char *));
	while (arr[++i])
		copy[i] = ft_strdup(arr[i]);
	copy[i] = NULL;
	return (copy);
}

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

bool	is_in_env(char **envp, char *var, int len)
{
	char	*str;
	char	*tmp;

	tmp = ft_substr(var, 0, len);
	str = find_variable(envp, tmp);
	free(tmp);
	return (str);
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

void	add_to_env_append2(char **env, char *line, int index)
{
	int 	i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], line, index) == 0)
		{
			if (ft_strchr(env[i], '='))
				tmp = ft_strjoin(env[i], &line[index + 2]);
			else
				tmp = ft_strjoin(env[i], &line[index + 1]);
			free(env[i]);
			env[i] = tmp;
		}
	}
}

void	add_to_env_append(char ***envp, char *line, int index)
{
	char	**env;
	char	*tmp;
	int		idx;

	if (!is_in_env(*envp, line, index))
	{
		idx = ft_strchr(line, '+') - line;
		tmp = ft_calloc(ft_strlen(line), sizeof(char));
		ft_strncpy(tmp, line, idx);
		ft_strncpy(&tmp[idx], &line[idx + 1], ft_strlen(line) - idx - 1);
		add_to_env_empty(envp, tmp);
		free(tmp);
		return ;
	}
	env = *envp;
	add_to_env_append2(env, line, index);
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
