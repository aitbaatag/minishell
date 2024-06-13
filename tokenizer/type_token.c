/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:07:47 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 22:18:53 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_type	check_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (WHITE_SPACE);
	return (WORD);
}

t_token_type	check_special_characters(char *str, int count)
{
	if (count == 1)
	{
		if (!ft_strcmp(str, ">"))
			return (OUTPUT_REDIRECTION);
		else if (!ft_strcmp(str, "<"))
			return (INPUT_REDIRECTION);
		else if (!ft_strcmp(str, "|"))
			return (PIPE);
		else if (!ft_strncmp(str, "(", 1))
			return (OPENING_PARENTHESES);
		else if (!ft_strncmp(str, ")", 1))
			return (CLOSING_PARENTHESES);
	}
	else if (count == 2)
	{
		if (!ft_strcmp(str, ">>"))
			return (APPEND_REDIRECTION);
		else if (!ft_strcmp(str, "<<"))
			return (HEREDOC);
		else if (!ft_strcmp(str, "&&"))
			return (AND);
		else if (!ft_strcmp(str, "||"))
			return (OR);
	}
	return (WORD);
}

t_token_type	return_type(char *str, int count)
{
	t_token_type	result;

	result = check_whitespace(*str);
	if (result != WORD)
		return (result);
	return (check_special_characters(str, count));
}
