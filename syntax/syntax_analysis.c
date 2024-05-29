#include "../include/minishell.h"

int	analyze(t_token *line)
{
	t_token	*crnt;
	// int		squote_count;
	// int		dquote_count;

	crnt = line;
	// squote_count = 0;
	// dquote_count = 0;
	while (crnt)
	{
		// if (crnt->type == SINGLE_QUOTE)
		// 	squote_count++;
		// else if (crnt->type == DOUBLE_QUOTE)
		// 	dquote_count++;
		if (crnt->type == AND || crnt->type == OR || crnt->type == PIPE)
			check_andorpipe(crnt);
		else if (crnt->type == OPENING_PARENTHESES)
			check_opening_parentheses(crnt);
		else if (crnt->type == CLOSING_PARENTHESES)
			check_closing_parentheses(crnt);
		else if (crnt->type == INPUT_REDIRECTION || crnt->type == HEREDOC || \
			crnt->type == OUTPUT_REDIRECTION || crnt->type == APPEND_REDIRECTION)
			check_redirection(crnt);
		else
			printf("check: word/space_encountred\n");
		crnt = crnt->next;
	}
	// if (squote_count % 2 || dquote_count % 2)
	// {
	// 	printf("minishell: syntax error\n");
	// 	exit(EXIT_FAILURE);
	// }
	return (0);
}
