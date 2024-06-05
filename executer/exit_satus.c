#include "../include/minishell.h"

// responsible for echo $?
int	get_exit_status(void)
{
	return (global.status);
}

void	set_exit_status(int status)
{
	global.status = status;
}

void	ft_function(int *status)
{
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = WTERMSIG(*status) + 128;
}