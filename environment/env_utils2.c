/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:57:53 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:10:05 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	get_envp_size(char **envp, t_env *envs, int i)
{
	size_t	size;
	t_env	*ptr_env;

	ptr_env = envs;
	size = 0;
	if (i == 0)
	{
		while (envp[size])
			size++;
	}
	else if (i == 1)
	{
		while (ptr_env)
		{
			ptr_env = ptr_env->next;
			size++;
		}
	}
	return (size);
}
