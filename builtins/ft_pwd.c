/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:12:41 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:12:44 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_exec *exec)
{
	char cwd[1024];

	(void)exec;
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (set_exit_status(0), get_exit_status());
}
