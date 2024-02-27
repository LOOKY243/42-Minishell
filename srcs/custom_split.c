/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:24:12 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/27 17:15:45 by gmarre           ###   ########.fr       */
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

	length = strlen(input_string);
	result = malloc(length * sizeof(char *));
	if (!result)
		return (NULL);
	result_index = 0;
	i = 0;
	while (i < length)
	{
		if (input_string[i] == '<')
		{
			if (input_string[i + 1] == '<')
			{
				result[result_index] = strdup("<<");
				result_index++;
				i += 2;
			}
			else
			{
				result[result_index] = strdup("<");
				result_index++;
				i++;
			}
		}
		else if (input_string[i] == '>')
		{
			if (i + 1 < length && input_string[i + 1] == '>')
			{
				result[result_index] = strdup(">>");
				result_index++;
				i += 2;
			}
			else
			{
				result[result_index] = strdup(">");
				result_index++;
				i++;
			}
		}
		else if (is_command_char(input_string[i], input_string[i + 1]))
			i++;
		else
		{
			j = i;
			while (j < length && !is_command_char(input_string[j],
					input_string[j + 1]))
				j++;
			result[result_index] = ft_substr(input_string, i, j - i);
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
