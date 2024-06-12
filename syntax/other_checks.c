#include "../include/minishell.h"

bool	check_parn_nbr(t_token *node)
{
	int	parn_nbr;

	parn_nbr = 0;
	while (node)
	{
		if (node->type == OPENING_PARENTHESES)
			parn_nbr++;
		else if (node->type == CLOSING_PARENTHESES)
			parn_nbr--;
		if (parn_nbr < 0)
		{
			ft_putstr_fd("minishell: syntax error, unclosed parentheses\n", 2);
			return (false);
		}
		node = node->next;
	}
	if (parn_nbr != 0)
	{
		ft_putstr_fd("minishell: syntax error, unclosed parentheses\n", 2);
		return (false);
	}
	return (true);
}

bool	check_closed_quotes(char *node, char quote)
{
	int	i;

	i = 0;
	while (node[i])
	{
		if (node[i] == quote)
		{
			i++;
			while (node[i] && node[i] != quote)
				i++;
			if (!node[i])
				return (false);
			else if (node[i] == quote)
				return (check_closed_quotes(&node[i + 1], quote));
		}
		i++;
	}
	return (true);
}

bool	check_series_of_redirection_after_parn(t_token *node)
{
	while (node)
	{
		if (node->next && node->next->next && node->next->next->next && \
		node->next->type & REDIRECTION && node->next->next->next->type == WORD)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			write(2, node->next->next->next->value, \
				ft_strlen(node->next->next->next->value));
			ft_putstr_fd("'\n", 2);
			return (false);
		}
		node = node->next;
	}
	return (true);
}
