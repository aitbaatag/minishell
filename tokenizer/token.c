/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:00:30 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/14 23:07:50 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process_spaces(t_token **tokens, char *line, int *i)
{
	int	fix;

	fix = *i;
	(void)tokens;
	while (line[*i] == 32 || (line[*i] >= 7 && line[*i] <= 13))
		(*i)++;
}

int	handle_special_characters(t_token **tokens, char *line, int *i)
{
	int	count;
	int	flag;
	int	fix;

	count = 0;
	flag = 0;
	fix = *i;
	while (line[*i] && line[*i] == line[fix] && count < 2)
	{
		if (line[*i] == '\"' || line[*i] == '\'')
		{
			flag = 1;
			is_quotes(tokens, &line[*i], i);
		}
		count++;
		(*i)++;
		if (return_type(&line[*i], 1) == OPENING_PARENTHESES
			|| return_type(&line[*i], 1) == CLOSING_PARENTHESES)
			break ;
	}
	if (flag == 0)
		add_token(tokens, ft_substr(&line[*i - count], 0, count), count);
	return (count);
}

void	handle_general_tokens(t_token **tokens, char *line, int *i)
{
	int	count;
	int	flag;
	int	save;
	int	b;

	b = 0;
	flag = 0;
	count = 0;
	save = -1;
	while (line[*i] && !is_special(line[*i], 0))
	{
		if ((line[*i] == '\"' || line[*i] == '\'') && !flag)
		{
			flag = 1;
			save = *i;
		}
		if (save >= 0 && line[save] == line[*i])
			b++;
		count++;
		(*i)++;
		if (b % 2 == 0 && (line[*i] == 32 || (line[*i] >= 7 \
			&& line[*i] <= 13)))
			break ;
	}
	add_token(tokens, ft_substr(&line[*i - count], 0, count), count);
}

t_token	*tokenization(char *line)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == 32 || (line[i] >= 7 && line[i] <= 13))
		{
			process_spaces(&tokens, line, &i);
		}
		else if (is_special(line[i], 1))
		{
			handle_special_characters(&tokens, line, &i);
		}
		else
			handle_general_tokens(&tokens, line, &i);
	}
	return (tokens);
}
