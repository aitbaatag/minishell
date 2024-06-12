/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:12:39 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 17:40:22 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exit_error(void)
{
	set_exit_status(2);
	free_garbage(&global.garbage_list);
	exit(get_exit_status());
}

static void	check_exit_args(char **args)
{
	int	i;

	if (!args[1])
	{
		ft_putstr_fd("exit\n", 2);
		free_garbage(&global.garbage_list);
		exit(EXIT_SUCCESS);
	}
	else if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit_error();
	}
	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putstr_fd("exit: \n", 2);
			write(2, args[1], ft_strlen(args[1]));
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_error();
		}
		i++;
	}
}

int	ft_exit(t_exec *exec)
{
	char	**args;

	args = exec->args;
	check_exit_args(args);
	ft_putstr_fd("exit\n", 2);
	set_exit_status(ft_atoi(args[1]));
	free_garbage(&global.garbage_list);
	exit(get_exit_status());
	return (get_exit_status());
}
