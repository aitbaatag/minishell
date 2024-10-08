/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:52 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 22:15:53 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_tree	*node_logic(t_token_type type, t_tree *left, t_tree *right)
{
	t_logic	*logical;

	logical = new_logic(type);
	logical->right = right;
	logical->left = left;
	return ((t_tree *)logical);
}

char	*init_arg(char *value)
{
	char	*arg;

	if (!value)
		return (NULL);
	arg = safe_malloc(ft_strlen(value) + 1);
	arg = ft_strdup(value);
	return (arg);
}

t_tree	*add_node_tree(t_tree *right, t_tree *left)
{
	t_pipe	*pipe;

	pipe = new_pipe();
	pipe->right = right;
	pipe->left = left;
	return ((t_tree *)pipe);
}
