/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/11 15:24:39 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	final = ft_strdup(tmp);
	free(tmp);
	free(str);
	return (final);
}

char	*change_cmd_env(t_program program, char *cmd)
{
	char	quote;
	char	*tmp;
	char	*env;
	char	*str;
	char	*oui;
	int		i;

	i = -1;
	str = ft_strdup(cmd);
	quote = '\0';
	while (str[++i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
		{
			quote = str[i];
			continue ;
		}
		if (quote == str[i])
		{
			quote = 0;
			continue ;
		}
		if (quote != '\'' && str[i] == '$')
		{
			if (ft_strlen_alnum(&str[i + 1]) == 0)
			{
				if (str[i + 1] == '?')
				{
					env = ft_itoa(program.exit_value);
					str = ft_replace(str, "?", env);
					free(env);
					continue ;
				}
				else
					continue ;
			}
			oui = ft_substr(&str[i + 1], 0, ft_strlen_alnum(&str[i + 1]));
			tmp = ft_strjoin(oui, "=");
			env = find_variable_secure(program.envp, tmp);
			if (!env)
				env = " ";
			str = ft_replace(str, oui, env);
			free(tmp);
			free(oui);
		}
	}
	return (str);
}

char	*remove_quote(char *str)
{
	int		i;
	int		offset;
	char	*tmp;
	char	*final;
	char	quote;

	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = -1;
	offset = 0;
	quote = 0;
	while (str[++i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
		{
			quote = str[i];
			++offset;
			continue ;
		}
		if (quote == str[i])
		{
			quote = 0;
			++offset;
			continue ;
		}
		tmp[i - offset] = str[i];
	}
	tmp[i - offset] = '\0';
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
