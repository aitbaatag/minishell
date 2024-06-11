#include "../include/minishell.h"

bool	check_andorpipe(t_token *node)
{
	if (!node->prev || (node->prev && !(node->prev->type & (WORD | CLOSING_PARENTHESES))))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write(2, node->value, 2);
		ft_putstr_fd("'\n", 2);
		return (false);
	}
	if (!node->next || (node->next && !(node->next->type & (WORD | REDIRECTION | OPENING_PARENTHESES))))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write(2, node->value, 2);
		ft_putstr_fd("'\n", 2);
		return (false);
	}
	return (true);
}

bool	check_parn_nbr(t_token *node)
{
	int parn_nbr;

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

bool	check_parentheses(t_token *node)
{
	if (node->type == OPENING_PARENTHESES)
	{
		if (node->prev && !(node->prev->type & (PIPE | LOGICAL | OPENING_PARENTHESES)))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			write(2, node->value, 2);
			ft_putstr_fd("'\n", 2);
			return (false);
		}
		if (node->next && !(node->next->type & (WORD | REDIRECTION | OPENING_PARENTHESES)))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			write(2, node->value, 2);
			ft_putstr_fd("'\n", 2);
			return (false);
		}
	}
	else
	{
		if (node->prev && !(node->prev->type & (WORD | CLOSING_PARENTHESES)))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			write(2, node->value, 2);
			ft_putstr_fd("'\n", 2);
			return (false);
		}
		if (node->next && !(node->next->type & (PIPE | LOGICAL | REDIRECTION | CLOSING_PARENTHESES)))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			write(2, node->value, 2);
			ft_putstr_fd("'\n", 2);
			return (false);
		}
		if (node->next && node->next->type & REDIRECTION)
		{
			while (node)
			{
				if (node->next && node->next->next && node->next->next->next && \
			node->next->type & REDIRECTION && node->next->next->next->type == WORD)
				{
					ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
					write(2, node->next->next->next->value, ft_strlen(node->next->next->next->value));
					ft_putstr_fd("'\n", 2);
					return (false);
				}
				node = node->next;
			}
		}
	}
	return (true);
}

bool	check_redirection(t_token *node)
{
	if (!node->next || (node->next && !(node->next->type & WORD)))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		write(2, node->value, 2);
		ft_putstr_fd("'\n", 2);
		return (false);
	}
	return (true);
}

bool	check_quotes1(char	*node)
{
	int	i = 0;
	while (node[i])
	{
		if (node[i] == '\'')
		{
			i++;
			while (node[i] && node[i] != '\'')
				i++;
			if (!node[i])
				return (false);
			else if (node[i] == '\'')
				return (check_quotes1(&node[i + 1]));
		}
		else if (node[i] == '\"')
		{
			i++;
			while (node[i] && node[i] != '\"')
				i++;
			if (!node[i])
				return (false);
			else if (node[i] == '\"')
				return (check_quotes1(&node[i + 1]));
		}
		else
			i++;
	}
	return (true);
}
