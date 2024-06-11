#include "../include/minishell.h"

int	ft_pwd(t_exec *exec)
{
	char cwd[1024];

	(void)exec;
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (set_exit_status(0), get_exit_status());
}