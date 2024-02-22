/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:26:18 by gmarre            #+#    #+#             */
/*   Updated: 2024/02/16 14:54:19 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_cmd_var(t_program program, char *cmd)
{
	char	**split;
	char *tmp;
	char	*env;
	char	*new_cmd;
	int	i;

	i = -1;
	split = ft_split_cmd(cmd, ' ');
	while(split[++i])
	{
		if (ft_strcmp(split[i], "$?") == 0)
		{
			free(split[i]);
			split[i] = ft_itoa(program.exit_value);
			continue;
		}
		env = find_variable(program.envp, &split[i][1]);
		if (env && env[0] == '=') {
			free(split[i]);
			split[i] = ft_strdup(&env[1]);
		}
	}
	i = -1;
	new_cmd = ft_calloc(1, sizeof(char));
	new_cmd[0] = '\0';
	while(split[++i])
	{
		tmp = ft_strjoin(new_cmd, split[i]);
		free(new_cmd);
		new_cmd = ft_strjoin(tmp, " ");
		free(tmp);
	}
	ft_freesplit(split);
	return (new_cmd);
}