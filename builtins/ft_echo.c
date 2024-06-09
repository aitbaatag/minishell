#include "../include/minishell.h"

int	check_echo_flag(char *str)
{
	int	index;

	index = 2;
	if (str[0] == '-' && str[1] && str[1] == 'n')
	{
		while (str[index])
		{
			if (str[index] != 'n')
				return (0);
			index++;
		}
		return (1);
	}
	return (0);
}

int ft_echo(t_exec *exec)
{
    char    **args;
	int		i;
	int		flag_exist;
	int		put_space;

    args = exec->args;
	i = 1;
	flag_exist = 0;
    while (args[i])
    { 
		if (check_echo_flag(args[i]))
		{
			flag_exist = 1;
			i++;
		}
		else
			break ;
	}
	put_space = 0;
	while (args[i])
	{
		if (put_space)
			printf(" ");
		printf("%s", args[i++]);
		put_space = 1;
	}
	if (!flag_exist)
		printf("\n");
    return(set_exit_status(0), get_exit_status());
}
