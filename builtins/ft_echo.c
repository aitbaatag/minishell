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

/* dosn't work because quotes qre removed; even if not */
// int	ft_put_space(t_exec *exec, int i)
// {
// 	printf("no_seg\n");
// 	if (exec->args[i + 1][0] == '\'' || exec->args[i + 1][0] == '\"' \
// 		|| exec->args[i][ft_strlen(exec->args[i]) - 1] == '\'' \
// 		|| exec->args[i][ft_strlen(exec->args[i]) - 1] == '\"')
// 		{
// 		printf("no_seg\n");
// 		return (0);
// 		}
// 	return (1);
// }

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
		if (put_space /*&& ft_put_space(exec, i)*/)
			printf(" ");
		printf("%s", args[i++]);
		put_space = 1;
	}
	if (!flag_exist)
		printf("\n");
    return(set_exit_status(0), get_exit_status());
}
