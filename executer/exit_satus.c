#include "../include/minishell.h"

int	get_exit_status(void)
{
	return (global.status);
}

void	set_exit_status(int status)
{
	global.status = status;
}

void	if_exit_with_signal(int *status)
{
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = WTERMSIG(*status) + 128;
}