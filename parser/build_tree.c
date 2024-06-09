#include "../include/parser.h"

t_tree	*grouoped_cmd_tree(t_token **tokens, t_tree *redi_list,
		t_redi_exec **list_heredoc)
{
	t_grp_exec	*grp;
	t_tree		*redi_child;
	t_tree		*mini_tree;

	redi_child = NULL;
	grp = new_grp_exec();
	if ((*tokens) && (*tokens)->type == CLOSING_PARENTHESES)
	{
		(*tokens) = (*tokens)->prev;
		mini_tree = pipe_tree(tokens, list_heredoc);
	}
	if ((*tokens) && ((*tokens)->type == AND || (*tokens)->type == OR))
		mini_tree = link_root_tree(tokens, mini_tree, list_heredoc);
	grp->child = mini_tree;
	grp->outer_redir = redi_list;
	if ((*tokens) && (*tokens)->type == OPENING_PARENTHESES)
		(*tokens) = (*tokens)->prev;
	return ((t_tree *)grp);
}

t_tree	*exec_tree(t_token **tokens)
{
	t_exec	*exec;
	t_token	*ptr;
	int		args;

	if (!(*tokens))
		return (NULL);
	ptr = (*tokens);
	args = 0;
	while (ptr && (ptr->type == WORD))
	{
		ptr = ptr->prev;
		args++;
	}
	ptr = (*tokens);
	exec = new_exec(args);
	while ((*tokens) && ((*tokens)->type == WORD))
	{
		exec->args[args - 1] = init_arg((*tokens)->value);
		(*tokens) = (*tokens)->prev;
		args--;
	}
	return ((t_tree *)exec);
}

t_tree	*link_root_tree(t_token **tokens, t_tree *right,
		t_redi_exec **list_heredoc)
{
	t_tree	*left;
	t_token	*ptr;

	left = NULL;
	ptr = (*tokens);
	if (!(*tokens))
		return (right);
	if ((*tokens)->type == AND || (*tokens)->type == OR)
	{
		(*tokens) = (*tokens)->prev;
		left = pipe_tree(tokens, list_heredoc);
		left = node_logic(ptr->type, link_root_tree(tokens, left, list_heredoc),
				right);
		return (left);
	}
	if (!(*tokens) || (*tokens)->type == OPENING_PARENTHESES)
		return (right);
	return (left);
}

t_tree	*pipe_tree(t_token **tokens, t_redi_exec **list_heredoc)
{
	t_tree	*tree_exec;

	if ((!*tokens))
		return (NULL);
	tree_exec = NULL;
	while ((*tokens))
	{
		if ((*tokens)->type == PIPE)
		{
			(*tokens) = (*tokens)->prev;
			tree_exec = add_node_tree(tree_exec, pipe_tree(tokens,
						list_heredoc));
		}
		else if ((*tokens)->type == CLOSING_PARENTHESES)
			tree_exec = grouoped_cmd_tree(tokens, tree_exec, list_heredoc);
		else if ((*tokens)->type == OPENING_PARENTHESES)
			return (tree_exec);
		else if ((*tokens)->type == OR || (*tokens)->type == AND)
			return (tree_exec);
		else if (visit_tokens(tokens))
			tree_exec = handling_redi(tokens, list_heredoc);
		else
			tree_exec = exec_tree(tokens);
	}
	return (tree_exec);
}
