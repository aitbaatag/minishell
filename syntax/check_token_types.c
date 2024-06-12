#include "../include/minishell.h"

void	print_syntax_error(t_token *node)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	write(2, node->value, 2);
	ft_putstr_fd("'\n", 2);
}

bool	check_andorpipe(t_token *node)
{
	if (!node->prev || (node->prev && \
		!(node->prev->type & (WORD | CLOSING_PARENTHESES))))
		return (print_syntax_error(node), false);
	if (!node->next || (node->next && \
		!(node->next->type & (WORD | REDIRECTION | OPENING_PARENTHESES))))
		return (print_syntax_error(node), false);
	return (true);
}

bool	check_parentheses(t_token *node)
{
	if (node->type == OPENING_PARENTHESES)
	{
		if (node->prev && \
			!(node->prev->type & (PIPE | LOGICAL | OPENING_PARENTHESES)))
			return (print_syntax_error(node), false);
		if (node->next && \
			!(node->next->type & (WORD | REDIRECTION | OPENING_PARENTHESES)))
			return (print_syntax_error(node), false);
	}
	else
	{
		if (node->prev && !(node->prev->type & (WORD | CLOSING_PARENTHESES)))
			return (print_syntax_error(node), false);
		if (node->next && !(node->next->type & \
			(PIPE | LOGICAL | REDIRECTION | CLOSING_PARENTHESES)))
			return (print_syntax_error(node), false);
		if (node->next && node->next->type & REDIRECTION)
		{
			if (!check_series_of_redirection_after_parn(node))
				return (false);
		}
	}
	return (true);
}

bool	check_redirection(t_token *node)
{
	int	i;

	i = 1;
	if (!node->next || (node->next && !(node->next->type & WORD)))
		return (print_syntax_error(node), false);
	return (true);
}
