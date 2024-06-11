#include "../include/parser.h"
// 	t_token	*ptr;
// 	int		size;

t_exec	*get_exec_and_update_tokens(t_token **tokens)
{
	t_exec	*exec_cmd;
	t_token	*ptr;
	t_token	*temp;
	int		size;

	size = 0;
	ptr = (*tokens);
	size = size_of_args(ptr);
	exec_cmd = new_exec(size);
	while (ptr)
	{
		if ((ptr->prev == NULL && ptr->type == WORD) || (ptr->type == WORD
				&& ptr->prev && (ptr->prev->type == WORD
					|| ptr->prev->type == PIPE || ptr->prev->type == AND
					|| ptr->prev->type == OR
					|| ptr->prev->type == OPENING_PARENTHESES)))
		{
			exec_cmd->args[size - 1] = init_arg(ptr->value);
			temp = ptr;
			if (ptr->prev)
				ptr->prev->next = ptr->next;
			if (ptr->next)
				ptr->next->prev = ptr->prev;
			if (ptr == (*tokens))
				(*tokens) = ptr->prev;
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
// void	process_tokens(t_token **tokens, t_exec *exec_cmd, int *size)
// {
// 	t_token	*ptr;
// 	t_token	*temp;

// 	ptr = *tokens;
// 	while (ptr)
// 	{
// 		if ((ptr->prev == NULL && ptr->type == WORD) || (ptr->type == WORD
// 				&& ptr->prev && (ptr->prev->type == WORD
// 						|| ptr->prev->type == PIPE || ptr->prev->type == AND
// 						|| ptr->prev->type == OR
// 					|| ptr->prev->type == OPENING_PARENTHESES)))
// 		{
// 			exec_cmd->args[*size - 1] = init_arg(ptr->value);
// 			temp = ptr;
// 			if (ptr->prev)
// 				ptr->prev->next = ptr->next;
// 			if (ptr->next)
// 				ptr->next->prev = ptr->prev;
// 			if (ptr == (*tokens))
// 				(*tokens) = ptr->prev;
// 			ptr = ptr->prev;
// 			(*size)--;
// 			free(temp->value);
// 			free(temp);
// 		}
// 		else
// 			ptr = ptr->prev;
// 	}
// }
// t_exec	*get_exec_and_update_tokens(t_token **tokens)
// {
// 	t_exec	*exec_cmd;
// 	t_token	*ptr;
// 	int		size;

// 	ptr = (*tokens);
// 	size = size_of_args(ptr);
// 	exec_cmd = new_exec(size);
// 	process_tokens(tokens, exec_cmd, &size);
// 	while (ptr)
// 	{
// 		if (ptr->type == CLOSING_PARENTHESES || ptr->type == OPENING_PARENTHESES
// 			|| ptr->type == PIPE || ptr->type == AND || ptr->type == OR)
// 		{
// 			return (exec_cmd);
// 		}
// 		ptr = ptr->prev;
// 	}
// 	return (exec_cmd);
// }

t_redi_exec	*get_node_heredoc(t_redi_exec **list_heredoc)
{
	t_redi_exec	*ptr;

	if (!list_heredoc || !(*list_heredoc))
	{
		return (NULL);
	}
	ptr = *list_heredoc;
	if ((*list_heredoc) && (*list_heredoc)->prev)
	{
		*list_heredoc = (*list_heredoc)->prev;
	}
	else
	{
		*list_heredoc = NULL;
	}
	return (ptr);
}

int	visit_tokens(t_token **tokens)
{
	t_token	*ptr;

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