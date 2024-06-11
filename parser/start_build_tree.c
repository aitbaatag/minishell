#include "../include/parser.h"

t_tree	*build_tree(t_token **tokens)
{
	t_redi_exec	*list_heredoc;
	t_tree		*tree;
	t_tree		*right;

	right = NULL;
	list_heredoc = creat_list_heredoc(*tokens);
	if (*heredoc_error() != -1 && !list_heredoc)
		return (NULL);
	reverse_list_tokens(tokens);
	right = pipe_tree(tokens, &list_heredoc);
	tree = link_root_tree(tokens, right, &list_heredoc);
	return (tree);
}
