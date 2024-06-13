/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:00:39 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 21:42:02 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_special(char c, int i)
{
	if (i == 1)
	{
		if (c == '<' || c == '>' || c == '&' || c == '|' || \
			c == '\"' || c == '\'' || c == '(' || c == ')')
			return (1);
	}
	else
	{
		if (c == '<' || c == '>' || c == '&' || c == '|' || c == '('
			|| c == ')')
			return (1);
	}
	return (0);
}

int	count_qoutes(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	is_quotes(t_token **token, char *str, int *i)
{
	t_token	*new_token;
	int		n;
	int		b;
	char	quote_char;

	quote_char = str[0];
	b = 1;
	n = 1;
	while (str[n])
	{
		if (str[n] == quote_char)
			b++;
		if (str[n] == str[0] && b % 2 == 0 && (str[n + 1] == 32 \
			|| is_special(str[n + 1], 0) || \
			(str[n + 1] >= 7 && str[n + 1] <= 13) || str[n + 1] == '\0'))
			break ;
		else if (b % 2 == 0 && ((str[n] == 32 || (str[n] >= 7 && \
			str[n] <= 13)) || is_special(str[n + 1], 0) || \
			(str[n + 1] == 32 || (str[n + 1] >= 7 && str[n + 1] <= 13))))
			break ;
		n++;
	}
	*i += n;
	new_token = new_node(ft_substr(str, 0, n + 1), return_type(str, 0));
	add_node_back(token, new_token);
}
