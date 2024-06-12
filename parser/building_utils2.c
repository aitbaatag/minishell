/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:52 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 18:38:25 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_tree	*node_logic(token type, t_tree *left, t_tree *right)
{
	t_logic	*logical;

	logical = new_logic(type);
	logical->right = right;
	logical->left = left;
	return ((t_tree *)logical);
}

char	*init_arg(char *value)
{
	int		i;
	char	*arg;

	i = 0;
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
