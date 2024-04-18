/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:06:21 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 16:07:40 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_env(char **envp, char *var, int len)
{
	char	*str;
	char	*tmp;

	tmp = ft_substr(var, 0, len);
	str = find_variable(envp, tmp);
	free(tmp);
	return (str);
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

void	add_to_env_append2(char **env, char *line, int index)
{
	int		i;
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
