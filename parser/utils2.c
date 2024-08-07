/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:06:43 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 18:38:08 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	check_expand(char *delimiter)
{
	int	len;

	len = ft_strlen(delimiter);
	return ((delimiter[0] != '\'' && delimiter[0] != '\"') \
		&& (delimiter[len - 1] != '\'' && delimiter[len - 1] != '\"'));
}

void	reverse_list_tokens(t_token **token)
{
	if (!token || !(*token))
		return ;
	while ((*token)->next)
		(*token) = (*token)->next;
}

int	size_of_args(t_token *token)
{
	t_token	*ptr;
	int		size;

	size = 0;
	ptr = token;
	while (ptr)
	{
		if ((ptr->prev == NULL && ptr->type == WORD) || (ptr->type == WORD
				&& ptr->prev && ptr->prev->type != INPUT_REDIRECTION
				&& ptr->prev->type != OUTPUT_REDIRECTION
				&& ptr->prev->type != APPEND_REDIRECTION
				&& ptr->prev->type != PARN && ptr->prev->type != HEREDOC))
			size++;
		else if (ptr->type == AND || ptr->type == OR || ptr->type == PIPE
			|| ptr->type == CLOSING_PARENTHESES)
			return (size);
		else if (ptr->prev == NULL && ptr->type == WORD)
			size++;
		ptr = ptr->prev;
	}
	return (size);
}
