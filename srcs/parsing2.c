/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/20 17:20:46 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_var(t_cmd_var *cmd_var)
{
	cmd_var->new_cmd = NULL;
	cmd_var->tmp = NULL;
	cmd_var->var_name = NULL;
	cmd_var->env_value = NULL;
	cmd_var->i = -1;
	cmd_var->start = 0;
	cmd_var->end = 0;
	cmd_var->len = 0;
}

int	change_cmd_var3(t_cmd_var *cmd_var, char *cmd)
{
	cmd_var->len = ft_strlen(cmd_var->new_cmd);
	cmd_var->tmp = ft_calloc(cmd_var->len + (cmd_var->i - cmd_var->start)
			+ ft_strlen(cmd_var->env_value) + 1, sizeof(char));
	if (!cmd_var->tmp)
	{
		free(cmd_var->var_name);
		free(cmd_var->new_cmd);
		return (0);
	}
	ft_strcpy(cmd_var->tmp, cmd_var->new_cmd);
	ft_strncpy(cmd_var->tmp + cmd_var->len, cmd + cmd_var->start, cmd_var->i
		- cmd_var->start);
	ft_strcpy(cmd_var->tmp + cmd_var->len + (cmd_var->i - cmd_var->start),
		cmd_var->env_value);
	free(cmd_var->new_cmd);
	cmd_var->new_cmd = cmd_var->tmp;
	cmd_var->start = cmd_var->end;
	return (1);
}

int	change_cmd_var4(t_cmd_var *cmd_var, char *cmd)
{
	cmd_var->len = ft_strlen(cmd_var->new_cmd);
	cmd_var->tmp = ft_calloc(cmd_var->len + (cmd_var->i - cmd_var->start) + 1, sizeof(char));
	if (!cmd_var->tmp)
	{
		free(cmd_var->var_name);
		free(cmd_var->new_cmd);
		return (0);
	}
	ft_strcpy(cmd_var->tmp, cmd_var->new_cmd);
	ft_strncpy(cmd_var->tmp + cmd_var->len, cmd + cmd_var->start, cmd_var->i
		- cmd_var->start);
	cmd_var->tmp[cmd_var->len + (cmd_var->i - cmd_var->start)] = '\0';
	free(cmd_var->new_cmd);
	cmd_var->new_cmd = cmd_var->tmp;
	cmd_var->start = cmd_var->end;
	return (1);
}

int	change_cmd_var2(t_program *program, t_cmd_var *cmd_var, char *cmd)
{
	while (cmd[++cmd_var->i])
	{
		if (cmd[cmd_var->i] == '$' && !is_separator(cmd[cmd_var->i + 1]))
		{
			cmd_var->end = cmd_var->i + 1;
			while (cmd[cmd_var->end] && !is_separator(cmd[cmd_var->end]))
				cmd_var->end++;
			cmd_var->var_name = ft_calloc(cmd_var->end - cmd_var->i, sizeof(char));
			ft_strncpy(cmd_var->var_name, cmd + cmd_var->i + 1, cmd_var->end
				- cmd_var->i - 1);
			cmd_var->env_value = find_variable(program->envp,
					cmd_var->var_name);
			if (cmd_var->env_value != NULL && cmd_var->env_value[0] == '=')
				cmd_var->env_value++;
			if (cmd_var->env_value)
			{
				if (!change_cmd_var3(cmd_var, cmd))
					return (0);
			}
			else if (!change_cmd_var4(cmd_var, cmd))
				return (0);
			free(cmd_var->var_name);
		}
	}
	return (1);
}

char	*change_cmd_var(t_program program, char *cmd)
{
	t_cmd_var	cmd_var;

	if (!cmd)
		return (NULL);
	init_cmd_var(&cmd_var);
	if (!change_cmd_var2(&program, &cmd_var, cmd))
		return (NULL);
	cmd_var.len = ft_strlen(cmd_var.new_cmd);
	cmd_var.tmp = ft_calloc(cmd_var.len + ft_strlen(cmd + cmd_var.start) + 1, sizeof(char));
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
