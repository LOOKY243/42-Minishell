/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarre <gmarre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:24:46 by gmarre            #+#    #+#             */
/*   Updated: 2024/04/29 16:29:49 by gmarre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && ft_strcmp(arr[i], "|"))
		i++;
	return (i);
}

char	*change_oldpwd(char *envp, char *pwd)
{
	char	*new;

	new = ft_strjoin("OLDPWD=", pwd);
	free(envp);
	return (new);
}

void	cd_loop(t_program *program)
{
	int		i;
	char	pwd[BUFFER_SIZE];

	i = 0;
	while (program->envp[i] && ft_strncmp("PWD=", program->envp[i], 4))
		i++;
	if (program->envp[i])
	{
		free(program->envp[i]);
		getcwd(pwd, sizeof(pwd));
		program->envp[i] = ft_strjoin("PWD=", pwd);
	}
}

int	special_cases(t_program *program, char *path)
{
	int		i;
	char	pwd[BUFFER_SIZE];

	i = 0;
	if (!path)
	{
		getcwd(pwd, sizeof(pwd));
		while (program->envp[i] && ft_strncmp("OLDPWD=", program->envp[i], 7))
			i++;
		if (program->envp[i])
			program->envp[i] = change_oldpwd(program->envp[i], pwd);
		chdir(find_variable(program->envp, "HOME="));
		return (1);
	}
	else if (path[0] == '-' && ft_strlen(path) == 1)
	{
		chdir(find_variable(program->envp, "OLDPWD="));
		if (!path)
			return (ENODATA);
		printf("%s\n", find_variable(program->envp, "OLDPWD="));
		return (1);
	}
	return (0);
}

int	cd(t_program *program, char *path)
{
	int		i;
	char	pwd[BUFFER_SIZE];
	char	*tmp;

	tmp = remove_quotes(path);
	path = tmp;
	i = special_cases(program, path);
	if (i)
	{
		free(path);
		if (i == ENODATA)
			return (ENODATA);
		return (0);
	}
	getcwd(pwd, sizeof(pwd));
	if (chdir(path) != 0)
		return (ENOENT);
	i = 0;
	while (program->envp[i] && ft_strncmp("OLDPWD=", program->envp[i], 7))
		i++;
	if (program->envp[i])
		program->envp[i] = change_oldpwd(program->envp[i], pwd);
	cd_loop(program);
	free(path);
	return (0);
}
