/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:58:00 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:10:05 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*find_env_var(t_env *envs, char *key)
{
	t_env	*current;

	current = envs;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key) + 1) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}
