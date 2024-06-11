#include "../include/parser.h"

int	is_argument_token(t_token *ptr)
{
	return (ptr->prev == NULL && ptr->type == WORD) ||
		(ptr->type == WORD && ptr->prev &&
			(ptr->prev->type == WORD || ptr->prev->type == PIPE ||
			ptr->prev->type == AND || ptr->prev->type == OR ||
			ptr->prev->type == OPENING_PARENTHESES));
}
void	remove_token(t_token **tokens, t_token *token)
{
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	if (token == *tokens)
		*tokens = token->prev;
}
t_exec	*get_exec_and_update_tokens(t_token **tokens)
{
	t_exec	*exec_cmd;
	t_token	*ptr;
	int		size;

	size = 0;
	ptr = (*tokens);
	size = size_of_args(ptr);
	exec_cmd = new_exec(size);
	while (ptr)
	{
		if (is_argument_token(ptr))
		{
			exec_cmd->args[size - 1] = init_arg(ptr->value);
			remove_token(tokens, ptr);
			ptr = ptr->prev;
			size--;
		}
		else if (ptr->type == CLOSING_PARENTHESES
				|| ptr->type == OPENING_PARENTHESES || ptr->type == PIPE
				|| ptr->type == AND || ptr->type == OR)
			return (exec_cmd);
		else
			ptr = ptr->prev;
	}
	return (exec_cmd);
}
t_redi_exec	*get_node_heredoc(t_redi_exec **list_heredoc)
{
	t_redi_exec	*ptr;

	if (!list_heredoc || !(*list_heredoc))
		return (NULL);
	ptr = *list_heredoc;
	if ((*list_heredoc) && (*list_heredoc)->prev)
		*list_heredoc = (*list_heredoc)->prev;
	else
		*list_heredoc = NULL;
	return (ptr);
}

int	visit_tokens(t_token **tokens)
{
	t_token *ptr;

	ptr = (*tokens);
	if (!ptr || !ptr->prev)
		return (0);
	while (ptr && ptr->prev && ptr->type != AND && ptr->type != OR
		&& ptr->type != PIPE && ptr->type != CLOSING_PARENTHESES
		&& ptr->type != OPENING_PARENTHESES)
	{
		if (ptr->type == WORD && (ptr->prev->type == INPUT_REDIRECTION
				|| ptr->prev->type == OUTPUT_REDIRECTION
				|| ptr->prev->type == APPEND_REDIRECTION
				|| ptr->prev->type == HEREDOC))
			return (1);
		ptr = ptr->prev;
	}
	return (0);
}