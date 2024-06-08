#include "../include/minishell.h"

static void	check_exit_args(char **args)
{
	int	i;

	if (!args[1])
		exit(EXIT_SUCCESS);
	else if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		set_exit_status(2);
		exit(get_exit_status());
	}
	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putstr_fd("exit: \n", 2);
			write(2, args[1], ft_strlen(args[1]));
			ft_putstr_fd(": numeric argument required\n", 2);
			set_exit_status(2);
			exit(get_exit_status());
		}
		i++;
	}
}

int ft_exit(t_exec *exec)
{
	char    **args;

	args = exec->args;
	check_exit_args(args);
	ft_putstr_fd("exit\n", 2);
	set_exit_status(ft_atoi(args[1]));
	exit(get_exit_status());
	return (get_exit_status());
}
