#include "../include/minishell.h"

bool	analyze_syntax(t_token *tokens)
{
	bool	no_error;

	no_error = true;
	no_error = check_parn_nbr(tokens);
	if (no_error == false)
		return (no_error);
	while (tokens)
	{
		if (tokens->type & LOGICAL || tokens->type == PIPE)
			no_error = check_andorpipe(tokens);
		else if (tokens->type & PARN)
			no_error = check_parentheses(tokens);
		else if (tokens->type & REDIRECTION)
			no_error = check_redirection(tokens);
		else if (tokens->type == WORD)
		{
			no_error = check_quotes1(tokens->value);
			if (no_error == false)
				ft_putstr_fd("syntax error: unclosed quotes\n", 2);
		}
		if (no_error == false)
		{
			set_exit_status(2);
			break ;
		}
		tokens = tokens->next;
	}
	return (no_error);
}