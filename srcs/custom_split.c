/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:24:12 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/18 16:04:51 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_starting_quote(t_custom_split *s, const char *input_string)
{
	if ((input_string[s->i] == '"' || input_string[s->i] == '\'')
		&& s->quote == '\0')
	{
		s->quote = input_string[s->i];
		s->result[s->result_index] = ft_calloc((s->length - s->i + 2),
				sizeof(char));
		s->result[s->result_index][0] = s->quote;
		s->j = s->i + 1;
		while (s->j < s->length && input_string[s->j] != s->quote)
		{
			s->result[s->result_index][s->j - s->i] = input_string[s->j];
			s->j++;
		}
		if (s->j < s->length && input_string[s->j] == s->quote)
		{
			s->result[s->result_index][s->j - s->i] = input_string[s->j];
			s->j++;
		}
		s->result[s->result_index][s->j - s->i + 1] = '\0';
		s->result_index++;
		s->i = s->j;
		s->quote = '\0';
		return (1);
	}
	return (0);
}

int	is_infile_sign(t_custom_split *s, const char *input_string)
{
	if (input_string[s->i] == '<')
	{
		if (input_string[s->i + 1] == '<')
		{
			s->result[s->result_index] = ft_strdup("<<");
			s->result_index++;
			s->i += 2;
		}
		else
		{
			s->result[s->result_index] = ft_strdup("<");
			s->result_index++;
			s->i++;
		}
		return (1);
	}
	return (0);
}

int	is_outfile_sign(t_custom_split *s, const char *input_string)
{
	if (input_string[s->i] == '>')
	{
		if (s->i + 1 < s->length && input_string[s->i + 1] == '>')
		{
			s->result[s->result_index] = ft_strdup(">>");
			s->result_index++;
			s->i += 2;
		}
		else
		{
			s->result[s->result_index] = ft_strdup(">");
			s->result_index++;
			s->i++;
		}
		return (1);
	}
	if (is_command_char(input_string[s->i], input_string[s->i + 1])
		&& s->quote == '\0')
		s->i++;
	return (0);
}

void	copy_rest(t_custom_split *s, const char *input_string)
{
	s->j = s->i;
	while (s->j < s->length && (!is_command_char(input_string[s->j],
				input_string[s->j + 1]) || s->quote != '\0'))
		s->j++;
	s->result[s->result_index] = ft_calloc((s->j - s->i + 1), sizeof(char));
	ft_memcpy(s->result[s->result_index], input_string + s->i, (s->j - s->i)
		* sizeof(char));
	s->result[s->result_index][s->j - s->i] = '\0';
	s->result_index++;
	s->i = s->j;
}

char	**custom_split(const char *input_string, int *count)
{
	t_custom_split	s;

	s.quote = '\0';
	s.length = ft_strlen(input_string);
	s.result = ft_calloc(s.length, sizeof(char *));
	if (!s.result)
		return (NULL);
	s.result_index = 0;
	s.i = 0;
	s.j = 0;
	while (s.i < s.length)
	{
		if (is_starting_quote(&s, input_string))
			continue ;
		else if (is_infile_sign(&s, input_string))
			continue ;
		else if (is_outfile_sign(&s, input_string))
			continue ;
		else
			copy_rest(&s, input_string);
	}
	*count = s.result_index;
	return (s.result);
}
