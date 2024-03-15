/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/15 16:35:42 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (0);
	return (1);
}

void	init_cmd_var(t_cmd_var *cmd_var)
{
	cmd_var->new_cmd = NULL;
	cmd_var->tmp = NULL;
	cmd_var->var_name = NULL;
	cmd_var->env_value = NULL;
	cmd_var->i = 0;
	cmd_var->start = 0;
	cmd_var->end = 0;
	cmd_var->len = 0;
}

char	*change_cmd_var(t_program program, char *cmd)
{
	t_cmd_var	cmd_var;

	if (!cmd)
		return (NULL);
	init_cmd_var(&cmd_var);
	while (cmd[cmd_var.i])
	{
		if (cmd[cmd_var.i] == '$' && !is_separator(cmd[cmd_var.i + 1]))
		{
			cmd_var.end = cmd_var.i + 1;
			while (cmd[cmd_var.end] && !is_separator(cmd[cmd_var.end]))
				cmd_var.end++;
			cmd_var.var_name = malloc(cmd_var.end - cmd_var.i);
			ft_strncpy(cmd_var.var_name, cmd + cmd_var.i + 1, cmd_var.end - cmd_var.i - 1);
			cmd_var.var_name[cmd_var.end - cmd_var.i - 1] = '\0';
			cmd_var.env_value = find_variable(program.envp, cmd_var.var_name);
			if (cmd_var.env_value != NULL && cmd_var.env_value[0] == '=')
				cmd_var.env_value++;
			if (cmd_var.env_value)
			{
				cmd_var.len = ft_strlen(cmd_var.new_cmd);
				cmd_var.tmp = malloc(cmd_var.len + (cmd_var.i - cmd_var.start) + ft_strlen(cmd_var.env_value) + 1);
				if (!cmd_var.tmp)
				{
					free(cmd_var.var_name);
					free(cmd_var.new_cmd);
					return (NULL);
				}
				ft_strcpy(cmd_var.tmp, cmd_var.new_cmd);
				ft_strncpy(cmd_var.tmp + cmd_var.len, cmd + cmd_var.start, cmd_var.i - cmd_var.start);
				ft_strcpy(cmd_var.tmp + cmd_var.len + (cmd_var.i - cmd_var.start), cmd_var.env_value);
				free(cmd_var.new_cmd);
				cmd_var.new_cmd = cmd_var.tmp;
				cmd_var.start = cmd_var.end;
			}
			else
			{
				cmd_var.len = ft_strlen(cmd_var.new_cmd);
				cmd_var.tmp = malloc(cmd_var.len + (cmd_var.i - cmd_var.start) + 1);
				if (!cmd_var.tmp)
				{
					free(cmd_var.var_name);
					free(cmd_var.new_cmd);
					return (NULL);
				}
				ft_strcpy(cmd_var.tmp, cmd_var.new_cmd);
				ft_strncpy(cmd_var.tmp + cmd_var.len, cmd + cmd_var.start, cmd_var.i - cmd_var.start);
				cmd_var.tmp[cmd_var.len + (cmd_var.i - cmd_var.start)] = '\0';
				free(cmd_var.new_cmd);
				cmd_var.new_cmd = cmd_var.tmp;
				cmd_var.start = cmd_var.end;
			}
			free(cmd_var.var_name);
		}
		cmd_var.i++;
	}
	cmd_var.len = ft_strlen(cmd_var.new_cmd);
	cmd_var.tmp = malloc(cmd_var.len + ft_strlen(cmd + cmd_var.start) + 1);
	if (!cmd_var.tmp)
	{
		free(cmd_var.new_cmd);
		return (NULL);
	}
	ft_strcpy(cmd_var.tmp, cmd_var.new_cmd);
	ft_strcpy(cmd_var.tmp + cmd_var.len, cmd + cmd_var.start);
	free(cmd_var.new_cmd);
	cmd_var.new_cmd = cmd_var.tmp;
	return (cmd_var.new_cmd);
}
