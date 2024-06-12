/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:03:19 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:10:05 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_notfound(char *cmd)
{
	int	i;
	int	backslash;

	ft_putstr_fd(cmd, 2);
	i = 0;
	backslash = 0;
	while (cmd[i])
		if (cmd[i++] == '/')
			backslash = 1;
	if (backslash)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd("\033[0;31m: command not found\n\033[0m", 2);
	set_exit_status(127);
}
