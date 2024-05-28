#include "../include/minishell.h"

void process_spaces(t_token **tokens, char *line, int *i)
{
	while (line[*i] == 32)
		(*i)++;
	add_token(tokens, ft_strdup(" "), 1);
}

int handle_special_characters(t_token **tokens, char *line, int *i)
{
	int count = 0;
	int flag = 0;
	int fix = *i;

	while (line[*i] && line[*i] == line[fix] && count < 2)
	{
		if (line[*i] == '\"' || line[*i] == '\'')
		{
			flag = 1;
			is_quotes(tokens, &line[*i], i);
		}
		count++;
		(*i)++;
		if (return_type(&line[*i], 1) == OPENING_PARENTHESES || return_type(&line[*i], 1) == CLOSING_PARENTHESES)
			break;
	}
	if (flag == 0)
		add_token(tokens, ft_substr(&line[*i - count], 0, count), count);

	return count;
}

void handle_general_tokens(t_token **tokens, char *line, int *i)
{
	int count = 0;

	while (line[*i] && line[*i] != 32 && !is_special(line[*i], 0))
	{
		count++;
		(*i)++;
	}
	add_token(tokens, ft_substr(&line[*i - count], 0, count), count);
}

t_token *tokenization(char *line)
{
	t_token *tokens = NULL;
	int i = 0;

	while (line[i])
	{
		if (line[i] == 32)
		{
			process_spaces(&tokens, line, &i);
		}
		else if (is_special(line[i], 1))
		{
			handle_special_characters(&tokens, line, &i);
		}
		else if (line[i] != 32 && !is_special(line[i], 0))
		{
			handle_general_tokens(&tokens, line, &i);
		}
	}
	return tokens;
}
