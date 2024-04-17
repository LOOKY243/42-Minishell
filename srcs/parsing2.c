/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/17 17:24:40 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_var(t_cmd_var *var)
{
	var->new_cmd = NULL;
	var->tmp = NULL;
	var->var_name = NULL;
	var->env_value = NULL;
	var->i = -1;
	var->start = 0;
	var->end = 0;
	var->len = 0;
}

int	change_cmd_var3(t_cmd_var *var, char *cmd)
{
	var->len = ft_strlen(var->new_cmd);
	var->tmp = ft_calloc(var->len + (var->i - var->start)
			+ ft_strlen(var->env_value) + 1, sizeof(char));
	if (!var->tmp)
	{
		free(var->var_name);
		free(var->new_cmd);
		return (0);
	}
	ft_strcpy(var->tmp, var->new_cmd);
	ft_strncpy(var->tmp + var->len, cmd + var->start, var->i - var->start);
	ft_strcpy(var->tmp + var->len + (var->i - var->start), var->env_value);
	free(var->new_cmd);
	var->new_cmd = var->tmp;
	var->start = var->end;
	return (1);
}

int	change_cmd_var4(t_cmd_var *var, char *cmd)
{
	var->len = ft_strlen(var->new_cmd);
	var->tmp = ft_calloc(var->len + (var->i - var->start) + 1, sizeof(char));
	if (!var->tmp)
	{
		free(var->var_name);
		free(var->new_cmd);
		return (0);
	}
	ft_strcpy(var->tmp, var->new_cmd);
	ft_strncpy(var->tmp + var->len, cmd + var->start, var->i - var->start);
	var->tmp[var->len + (var->i - var->start)] = '\0';
	free(var->new_cmd);
	var->new_cmd = var->tmp;
	var->start = var->end;
	return (1);
}

int	change_cmd_var2(t_program *program, t_cmd_var *var, char *cmd)
{
	while (cmd[++var->i])
	{
		if (cmd[var->i] == '$' && !is_separator(cmd[var->i + 1]))
		{
			var->end = var->i + 1;
			while (cmd[var->end] && !is_separator(cmd[var->end]))
				var->end++;
			var->var_name = ft_calloc(var->end - var->i, sizeof(char));
			ft_strncpy(var->var_name, cmd + var->i + 1, var->end - var->i - 1);
			var->env_value = find_variable(program->envp, var->var_name);
			if (var->env_value != NULL && var->env_value[0] == '=')
				var->env_value++;
			if (var->env_value)
			{
				if (!change_cmd_var3(var, cmd))
					return (0);
			}
			else if (!change_cmd_var4(var, cmd))
				return (0);
			free(var->var_name);
		}
	}
	return (1);
}

char	*change_cmd_var(t_program program, char *cmd)
{
	t_cmd_var	var;

	if (!cmd)
		return (NULL);
	init_cmd_var(&var);
	if (!change_cmd_var2(&program, &var, cmd))
		return (NULL);
	var.len = ft_strlen(var.new_cmd);
	var.tmp = ft_calloc(var.len + ft_strlen(cmd + var.start) + 1, sizeof(char));
	if (!var.tmp)
	{
		free(var.new_cmd);
		return (NULL);
	}
	ft_strcpy(var.tmp, var.new_cmd);
	ft_strcpy(var.tmp + var.len, cmd + var.start);
	free(var.new_cmd);
	var.new_cmd = var.tmp;
	return (var.new_cmd);
}
