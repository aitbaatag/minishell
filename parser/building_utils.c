/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:59:50 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 22:16:31 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_pipe	*new_pipe(void)
{
	t_pipe	*pipe;

	pipe = safe_malloc(sizeof(t_pipe));
	pipe->type = PIPE;
	pipe->right = NULL;
	pipe->left = NULL;
	return (pipe);
}

t_exec	*new_exec(int size_of_args)
{
	t_exec	*exec;

	if (!size_of_args)
		return (NULL);
	exec = safe_malloc(sizeof(t_exec));
	exec->args = safe_malloc(sizeof(char *) * (size_of_args + 1));
	exec->args[size_of_args] = NULL;
	exec->line = NULL;
	exec->child_redi = NULL;
	exec->type = EXEC;
	return (exec);
}

t_grp_exec	*new_grp_exec(void)
{
	t_grp_exec	*grp_exec;

	grp_exec = safe_malloc(sizeof(t_grp_exec));
	grp_exec->type = SUBSHELL;
	grp_exec->child = NULL;
	grp_exec->outer_redir = NULL;
	return (grp_exec);
}

t_logic	*new_logic(t_token_type type)
{
	t_logic	*lo_oper;

	lo_oper = safe_malloc(sizeof(t_token));
	lo_oper->type = type;
	lo_oper->left = NULL;
	lo_oper->left = NULL;
	return (lo_oper);
}

t_redi_exec	*new_redi(t_token **tokens)
{
	t_redi_exec	*redi;

	redi = safe_malloc(sizeof(t_redi_exec));
	redi->type = (*tokens)->prev->type;
	if (redi->type == INPUT_REDIRECTION)
	{
		redi->flags = O_RDONLY;
	}
	else if (redi->type == OUTPUT_REDIRECTION
		|| redi->type == APPEND_REDIRECTION)
	{
		redi->flags = O_WRONLY | O_CREAT;
		if (redi->type == APPEND_REDIRECTION)
			redi->flags |= O_APPEND;
		if (redi->type == OUTPUT_REDIRECTION)
			redi->flags |= O_TRUNC;
	}
	redi->dlmt = NULL;
	redi->exec_child = NULL;
	redi->next = NULL;
	redi->prev = NULL;
	redi->file_name = (*tokens)->value;
	return (redi);
}
