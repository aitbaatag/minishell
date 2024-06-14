/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:12:39 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/14 09:08:08 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exit_error(int status)
{
	set_exit_status(status);
	free_garbage(&g_global.garbage_list);
	exit(get_exit_status());
}

static void	check_exit_args(char **args)
{
	int	i;

	if (!args[1])
	{
		ft_putstr_fd("exit\n", 2);
		exit_error(0);
	}
	else if (args[2])
	{
		ft_putstr_fd(RED "exit: too many arguments\n"CLOSE, 2);
		set_exit_status(2);
	}
	i = -1;
	if (args[1][0] == '-' || args[1][0] == '+')
		i++;
	while (args[1][++i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putstr_fd("exit: \n", 2);
			write(2, args[1], ft_strlen(args[1]));
			ft_putstr_fd(RED": numeric argument required\n"CLOSE, 2);
			exit_error(2);
		}
	}
}

int	ft_exit(t_exec *exec)
{
	char	**args;

	args = exec->args;
	check_exit_args(args);
	ft_putstr_fd("exit\n", 2);
	set_exit_status(ft_atoi(args[1]));
	free_garbage(&g_global.garbage_list);
	exit(get_exit_status());
	return (get_exit_status());
}
