/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/17 17:25:23 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace2(char *str, char *tmp)
{
	char	*final;

	final = ft_strdup(tmp);
	free(tmp);
	free(str);
	return (final);
}

char	*ft_replace(char *str, char *toReplace, char *replacer)
{
	int		i;
	int		j;
	char	*tmp;
	char	*final;

	tmp = ft_calloc(ft_strlen(str) + ft_strlen(replacer) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_strncmp(&str[i], toReplace, ft_strlen(toReplace)) != 0 || j != 0)
		{
			tmp[i + j] = str[i];
			i++;
			continue ;
		}
		j = -1;
		while (replacer[++j])
			tmp[i + j - 1] = replacer[j];
		i += ft_strlen(toReplace);
		j = ft_strlen(replacer) - ft_strlen(toReplace) - 1;
	}
	tmp[i + j] = '\0';
	final = ft_replace2(str, tmp);
	return (final);
}

void	change_cmd_env2(t_change_cmd_env *cmd_env, t_program *program)
{
	if (cmd_env->quote != '\'' && cmd_env->str[cmd_env->i] == '$')
	{
		if (ft_strlen_alnum(&cmd_env->str[cmd_env->i + 1]) == 0)
		{
			if (cmd_env->str[cmd_env->i + 1] == '?')
			{
				cmd_env->env = ft_itoa(program->exit_value);
				cmd_env->str = ft_replace(cmd_env->str, "?", cmd_env->env);
				free(cmd_env->env);
				return ;
			}
			else
				return ;
		}
		cmd_env->oui = ft_substr(&cmd_env->str[cmd_env->i + 1], 0,
				ft_strlen_alnum(&cmd_env->str[cmd_env->i + 1]));
		cmd_env->tmp = ft_strjoin(cmd_env->oui, "=");
		cmd_env->env = find_variable_secure(program->envp, cmd_env->tmp);
		if (!cmd_env->env)
			cmd_env->env = " ";
		cmd_env->str = ft_replace(cmd_env->str, cmd_env->oui, cmd_env->env);
		free(cmd_env->tmp);
		free(cmd_env->oui);
	}
}

char	*change_cmd_env(t_program program, char *cmd)
{
	t_change_cmd_env	cmd_env;

	cmd_env.i = -1;
	cmd_env.str = ft_strdup(cmd);
	cmd_env.quote = '\0';
	while (cmd_env.str[++cmd_env.i])
	{
		if (!cmd_env.quote && (cmd_env.str[cmd_env.i] == '\''
				|| cmd_env.str[cmd_env.i] == '"'))
		{
			cmd_env.quote = cmd_env.str[cmd_env.i];
			continue ;
		}
		if (cmd_env.quote == cmd_env.str[cmd_env.i])
		{
			cmd_env.quote = 0;
			continue ;
		}
		change_cmd_env2(&cmd_env, &program);
	}
	return (cmd_env.str);
}

int	remove_quote2(char *str, char *quote, int *offset, int i)
{
	if (!quote && (str[i] == '\'' || str[i] == '\"'))
	{
		*quote = str[i];
		++offset;
		return (1);
	}
	return (0);
}

char	*remove_quote(char *str)
{
	int		i[2];
	char	*tmp;
	char	*final;
	char	quote;

	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i[0] = -1;
	i[1] = 0;
	quote = 0;
	while (str[++i[0]])
	{
		if (remove_quote2(str, &quote, &i[1], i[0]))
			continue ;
		else if (quote == str[i[0]])
		{
			quote = 0;
			++i[1];
		}
		else
			tmp[i[0] - i[1]] = str[i[0]];
	}
	tmp[i[0] - i[1]] = '\0';
	final = ft_strdup(tmp);
	free(tmp);
	return (final);
}

void	remove_quote_split(int start, char **split)
{
	int		i;
	char	*tmp;

	if (!split)
		return ;
	i = start;
	while (split[i])
	{
		tmp = remove_quote(split[i]);
		free(split[i]);
		split[i] = tmp;
		++i;
	}
}

char	*treat_cmd(t_program program, char *cmd)
{
	char	*final;

	final = change_cmd_env(program, cmd);
	return (final);
}
