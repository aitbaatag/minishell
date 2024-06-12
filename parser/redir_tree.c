/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:00:05 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 18:40:30 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_redi_exec	*handle_redirection(t_token **tokens, t_redi_exec **list_heredoc)
{
	t_redi_exec	*redi_exec;

	redi_exec = NULL;
	if ((*tokens) && (*tokens)->prev)
	{
		if ((*tokens)->prev->type == HEREDOC)
			redi_exec = get_node_heredoc(list_heredoc);
		else if ((*tokens)->prev->type == INPUT_REDIRECTION || \
			(*tokens)->prev->type == OUTPUT_REDIRECTION || \
			(*tokens)->prev->type == APPEND_REDIRECTION)
		{
			redi_exec = new_redi(tokens);
		}
		if ((*tokens)->prev)
		{
			if ((*tokens)->prev->prev)
				(*tokens) = (*tokens)->prev->prev;
			else
				(*tokens) = NULL;
		}
	}
	return (redi_exec);
}

t_tree	*handling_redi(t_token **tokens, t_redi_exec **list_heredoc)
{
	t_redi_exec	*redi_exec;
	t_exec		*exec;

	redi_exec = NULL;
	exec = NULL;
	if (!(*tokens) || !tokens)
		return (NULL);
	exec = get_exec_and_update_tokens(tokens);
	redi_exec = handle_redirection(tokens, list_heredoc);
	if ((*tokens) && (*tokens)->prev && \
		((*tokens)->prev->type == INPUT_REDIRECTION || \
		(*tokens)->prev->type == OUTPUT_REDIRECTION || \
		(*tokens)->prev->type == APPEND_REDIRECTION || \
		(*tokens)->prev->type == HEREDOC))
	{
		redi_exec->exec_child = (t_tree *)handling_redi(tokens, list_heredoc);
	}
	if (exec)
	{
		exec->child_redi = (t_tree *)redi_exec;
		return ((t_tree *)exec);
	}
	return ((t_tree *)redi_exec);
}
