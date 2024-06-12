/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_build_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:00:07 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:10:05 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_tree	*build_tree(t_token **tokens)
{
	t_redi_exec	*list_heredoc;
	t_tree		*tree;
	t_tree		*right;

	right = NULL;
	list_heredoc = creat_list_heredoc(*tokens);
	if (*heredoc_signaled() != -1 && !list_heredoc)
		return (NULL);
	reverse_list_tokens(tokens);
	right = pipe_tree(tokens, &list_heredoc);
	tree = link_root_tree(tokens, right, &list_heredoc);
	return (tree);
}
