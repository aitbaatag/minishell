#include "../include/minishell.h"

void	check_andorpipe(t_token *node)
{
	printf("check: and_or_pipe\n");
	if (node->prev == NULL || (node->prev->type != 9 && node->prev->type != 8 \
		&& node->prev->type != 14 && node->prev->type != 10 && \
		node->prev->type != 0 && node->prev->type != 12 && \
		node->prev->type != 13))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", node->value);
		exit(EXIT_FAILURE);
	}
	if (node->next == NULL || (node->next->type == 1 || node->next->type == 6 \
		|| node->next->type == 7 || node->next->type == 12))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", node->value);
		exit(EXIT_FAILURE);
	}
}

void	check_opening_parentheses(t_token *node)
{
	printf("check: opening_parentheses\n");
	if (node->prev != NULL && node->prev->type != 6 && node->prev->type != 7 \
		&& node->prev->type != 1 && node->prev->type != 11 && node->prev->type != 13)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", node->value);
		exit(EXIT_FAILURE);
	}
	if (node->next == NULL || (node->next->type == 1 || node->next->type == 6 \
		|| node->next->type == 7 || node->next->type == 12))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", node->value);
		exit(EXIT_FAILURE);
	}
}

void	check_closing_parentheses(t_token *node)
{
	printf("check: closing_parentheses\n");
	if (node->prev == NULL || (node->prev->type != 9 && node->prev->type != 8 \
		&& node->prev->type != 14 && node->prev->type != 10 && \
		node->prev->type != 0 && node->prev->type != 12 && \
		node->prev->type != 13))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", node->value);
		exit(EXIT_FAILURE);
	}
	if (node->next && node->next->type != 13 && node->next->type != 12 && \
		node->next->type != 1 && node->next->type != 6 && \
		node->next->type != 7)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", node->value);
		exit(EXIT_FAILURE);
	}
}

void check_redirection(t_token *node)
{
	printf("check: redirection\n");
	if (node->next == NULL || (node->next->type != 9 && node->next->type != 8 \
		&& node->next->type != 14 && node->next->type != 10 && \
		node->next->type != 0 && node->next->type != 13))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", node->value);
		exit(EXIT_FAILURE);
	}
}

// printf("minishell: syntax error near unexpected token `%s'\n", node->value);