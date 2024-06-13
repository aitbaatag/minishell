/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:57:37 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 22:14:32 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_unset(char *key)
{
	t_env	*key_node;

	key_node = find_env_var(g_global.env, key);
	if (key_node)
	{
		if (key_node->prev)
			key_node->prev->next = key_node->next;
		else
			g_global.env = key_node->next;
		if (key_node->next)
			key_node->next->prev = key_node->prev;
	}
	return (0);
}

int	ft_unset(t_exec *exec)
{
	int	i;

	i = 1;
	while (exec->args[i])
		builtin_unset(exec->args[i++]);
	return (set_exit_status(0), get_exit_status());
}
