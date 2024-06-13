/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_satus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:58:07 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 22:14:32 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_exit_status(void)
{
	return (g_global.status);
}

void	set_exit_status(int status)
{
	g_global.status = status;
}

void	if_exit_with_signal(int *status)
{
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = WTERMSIG(*status) + 128;
}
