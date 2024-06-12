/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:07:47 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 19:18:10 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

token	check_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (WHITE_SPACE);
	return (WORD);
}

token	check_special_characters(char *str, int count)
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

token	return_type(char *str, int count)
{
	token	result;

	result = check_whitespace(*str);
	if (result != WORD)
		return (result);
	return (check_special_characters(str, count));
}
