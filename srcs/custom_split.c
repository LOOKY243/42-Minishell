/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:24:12 by gmarre            #+#    #+#             */
/*   Updated: 2024/03/22 12:22:18 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command_char(char c, char next)
{
	return (c == ' ' || c == '<' || c == '>' || (c == ' ' && (next == '<'
				|| next == '>')));
}

char	**custom_split(const char *input_string, int *count)
{
	int		length;
	char	**result;
	int		result_index;
	int		i;
	int		j;
	char	quote;

	quote = '\0';
	length = ft_strlen(input_string);
	result = ft_calloc(length, sizeof(char *));
	if (!result)
		return (NULL);
	result_index = 0;
	i = 0;
	while (i < length)
	{
		if ((input_string[i] == '"' || input_string[i] == '\'')
				&& quote == '\0')
		{
			quote = input_string[i];
			result[result_index] = ft_calloc((length - i + 2), sizeof(char));
			result[result_index][0] = quote;
			j = i + 1;
			while (j < length && input_string[j] != quote)
			{
				result[result_index][j - i] = input_string[j];
				j++;
			}
			if (j < length && input_string[j] == quote)
			{
				result[result_index][j - i] = input_string[j];
				j++;
			}
			result[result_index][j - i + 1] = '\0';
			result_index++;
			i = j;
			quote = '\0';
		}
		else if (input_string[i] == '<')
		{
			if (input_string[i + 1] == '<')
			{
				result[result_index] = ft_strdup("<<");
				result_index++;
				i += 2;
			}
			else
			{
				result[result_index] = ft_strdup("<");
				result_index++;
				i++;
			}
		}
		else if (input_string[i] == '>')
		{
			if (i + 1 < length && input_string[i + 1] == '>')
			{
				result[result_index] = ft_strdup(">>");
				result_index++;
				i += 2;
			}
			else
			{
				result[result_index] = ft_strdup(">");
				result_index++;
				i++;
			}
		}
		else if (is_command_char(input_string[i], input_string[i + 1])
			&& quote == '\0')
			i++;
		else
		{
			j = i;
			while (j < length && (!is_command_char(input_string[j],
						input_string[j + 1]) || quote != '\0'))
				j++;
			result[result_index] = ft_calloc((j - i + 1), sizeof(char));
			ft_memcpy(result[result_index], input_string + i, (j - i)
				* sizeof(char));
			result[result_index][j - i] = '\0';
			result_index++;
			i = j;
		}
	}
	*count = result_index;
	return (result);
}

void	free_result(char **result, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		free(result[i]);
	free(result);
}
