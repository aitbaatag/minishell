#include "../include/minishell.h"

bool	select_check(t_token *tokens, bool *status)
{
	while (tokens)
	{
		if (tokens->type & LOGICAL || tokens->type == PIPE)
			*status = check_andorpipe(tokens);
		else if (tokens->type & PARN)
			*status = check_parentheses(tokens);
		else if (tokens->type & REDIRECTION)
			*status = check_redirection(tokens);
		else if (tokens->type == WORD)
		{
			*status = check_closed_quotes(tokens->value, '\'') && \
					check_closed_quotes(tokens->value, '\"');
			if (*status == false)
				ft_putstr_fd("minishell: syntax error, unclosed quotes\n", 2);
		}
		if (*status == false)
		{
			set_exit_status(2);
			break ;
		}
		tokens = tokens->next;
	}
	return (*status);
}

bool	ambiguous_redirect(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type != HEREDOC && tokens->next && tokens->next->value[0] == '*')
		{
			while (tokens->next->value[i] == '*')
				i++;
			if (tokens->next->value[i] == '\0')
			{
				ft_putstr_fd("minishell: ", 2);
				write(2, tokens->next->value, ft_strlen(tokens->next->value));
				ft_putstr_fd(": ambiguous redirect\n", 2);
				return (set_exit_status(1), false);
			}
		}
		tokens = tokens->next;
	}
	return (true);
}

bool	analyze_syntax(t_token *tokens)
{
	bool	no_error;

	no_error = true;
	no_error = check_parn_nbr(tokens);
	if (no_error == false)
	{
		set_exit_status(2);
		return (no_error);
	}
	select_check(tokens, &no_error);
	return (no_error);
}
