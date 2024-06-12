/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:12:41 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 17:09:00 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_exec *exec)
{
	char	cwd[1024];

	(void)exec;
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (set_exit_status(0), get_exit_status());
}
