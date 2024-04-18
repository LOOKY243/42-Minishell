/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 16:15:05 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
