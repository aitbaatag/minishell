/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:58:05 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 21:13:17 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	run_logic(t_tree *tree)
{
	t_logic	*logic;
	int		status;

	logic = (t_logic *)tree;
	status = 0;
	if (logic->type == AND)
	{
		status = ft_run_node(logic->left);
		if (status == EXIT_SUCCESS)
			status = ft_run_node(logic->right);
	}
	else if (logic->type == OR)
	{
		status = ft_run_node(logic->left);
		if (status != EXIT_SUCCESS && status != 130)
			status = ft_run_node(logic->right);
	}
	return (set_exit_status(status), get_exit_status());
}
