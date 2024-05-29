#include "../include/minishell.h"

// responsible for echo $?
int		get_exit_status(void)
{
    return (global->status);
}

void	set_exit_status(int status)
{
    global->status = status;
}