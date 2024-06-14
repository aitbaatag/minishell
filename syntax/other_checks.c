/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:00:25 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/14 01:36:23 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static bool	check_quotes_core(char *node, int *i, char quote)
{
	(*i)++;
	while (node[*i] && node[*i] != quote)
		(*i)++;
	if (!node[*i])
		return (false);
	else if (node[*i] == quote)
		return (check_closed_quotes(&node[*i + 1]));
	return (true);
}

bool	check_closed_quotes(char *node)
{
	int	i;

	i = 0;
	while (node[i])
	{
		if (node[i] == '\'')
			return (check_quotes_core(node, &i, '\''));
		else if (node[i] == '\"')
			return (check_quotes_core(node, &i, '\"'));
		else
			i++;
	}
	return (true);
}

bool	check_series_of_redirection_after_parn(t_token *node)
{
	while (node)
	{
		if (node->next && node->next->next && node->next->next->next && \
			node->next->type & REDIRECTION && \
			node->next->next->next->type == WORD)
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
