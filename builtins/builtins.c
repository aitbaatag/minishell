#include "../include/minishell.h"

int	(*is_builtin(char *cmd))(t_exec *exec)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd);
	else if (ft_strcmp(cmd, "export") == 0)
		return (export_env_var);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset);
	else if (ft_strcmp(cmd, "env") == 0)
		return (builtin_env);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit);
	return (NULL);
}