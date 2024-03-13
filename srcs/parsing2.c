/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/13 16:44:50 by ycostode         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (0);
	return (1);
}

char	*change_cmd_var(t_program program, char *cmd)
{
	char	*new_cmd;
	char	*tmp;
	char	*var_name;
	char	*env_value;
	int		i;
	int		start;
	int		end;
	int		len;

	new_cmd = NULL;
	tmp = NULL;
	var_name = NULL;
	env_value = NULL;
	i = 0;
	start = 0;
	end = 0;
	len = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && !is_separator(cmd[i + 1]))
		{
			end = i + 1;
			while (cmd[end] && !is_separator(cmd[end]))
				end++;
			var_name = malloc(end - i);
			ft_strncpy(var_name, cmd + i + 1, end - i - 1);
			var_name[end - i - 1] = '\0';
			env_value = find_variable(program.envp, var_name);
			if (env_value != NULL && env_value[0] == '=')
				env_value++;
			if (env_value)
			{
				len = ft_strlen(new_cmd);
				tmp = malloc(len + (i - start) + ft_strlen(env_value) + 1);
				if (!tmp)
				{
					free(var_name);
					free(new_cmd);
					return (NULL);
				}
				ft_strcpy(tmp, new_cmd);
				ft_strncpy(tmp + len, cmd + start, i - start);
				ft_strcpy(tmp + len + (i - start), env_value);
				free(new_cmd);
				new_cmd = tmp;
				start = end;
			}
			else
			{
				len = ft_strlen(new_cmd);
				tmp = malloc(len + (i - start) + 1);
				if (!tmp)
				{
					free(var_name);
					free(new_cmd);
					return (NULL);
				}
				ft_strcpy(tmp, new_cmd);
				ft_strncpy(tmp + len, cmd + start, i - start);
				tmp[len + (i - start)] = '\0';
				free(new_cmd);
				new_cmd = tmp;
				start = end;
			}
			free(var_name);
		}
		i++;
	}
	len = ft_strlen(new_cmd);
	tmp = malloc(len + ft_strlen(cmd + start) + 1);
	if (!tmp)
	{
		free(new_cmd);
		return (NULL);
	}
	ft_strcpy(tmp, new_cmd);
	ft_strcpy(tmp + len, cmd + start);
	free(new_cmd);
	new_cmd = tmp;
	return (new_cmd);
}
