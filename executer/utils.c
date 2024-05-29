#include "../include/minishell.h"
void free_it(char **split_path)
{
	int i;

	i = 0;
	while (split_path[i])
		free(split_path[i++]);
	free (split_path);
}
char	*check_path(char *path, char *command)
{
	char	*valid_command;

	valid_command = ft_strjoin(path, command);
	if (access(valid_command, X_OK) == 0)
		return (valid_command);
	else
		return (free(valid_command), NULL);
}
char	*get_path(char *command)
{
	int		i;
	char	**split_path;
	t_env	*path_node;
	char	*valid_path;
	char	*curpath;

	i = 0;
	if (command == NULL)
		return (NULL);
	if (access(command, X_OK) == 0)
		return (command);
	// if ((command[0] == '/' || command[0] == '.'))
	// 	return (NULL);
	path_node = find_env_var(global.env, "PATH");
	split_path = ft_split(path_node->value, ':');
	if (split_path)
	{
		while (split_path[i] != NULL)
		{
			curpath = ft_strjoin(split_path[i], "/");
			valid_path = check_path(curpath, command);
			free (curpath);
			if (valid_path != NULL)
				return (free_it(split_path), valid_path);
			free (valid_path);
			i++;
		}
	}
	return (NULL);
}

int	check_cmd(t_exec *exec)
{
	(void)exec;
	return (0);
}