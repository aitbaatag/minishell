/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:58:09 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/14 06:25:17 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_path(char *path, char *command)
{
	char	*valid_command;

	valid_command = ft_strjoin(path, command);
	if (access(valid_command, X_OK) == 0)
		return (valid_command);
	else
		return (NULL);
}

char	*find_valid_path(char **split_path, char *command)
{
	char	*curpath;
	char	*valid_path;
	int		i;

	i = 0;
	while (split_path[i] != NULL)
	{
		curpath = ft_strjoin(split_path[i], "/");
		valid_path = check_path(curpath, command);
		if (valid_path != NULL)
			return (valid_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *command)
{
	char		**split_path;
	t_env		*path_node;
	char		*valid_path;
	struct stat	info;

	stat(command, &info);
	if (command == NULL)
		return (NULL);
	if (access(command, X_OK) == 0 && !S_ISDIR(info.st_mode))
		return (command);
	if ((command[0] == '/' || command[0] == '.'))
		return (command);
	path_node = find_env_var(g_global.env, "PATH");
	if (!path_node)
		return (NULL);
	split_path = ft_split(path_node->value, ':');
	if (split_path)
	{
		valid_path = find_valid_path(split_path, command);
		if (valid_path)
			return (valid_path);
	}
	return (command);
}
