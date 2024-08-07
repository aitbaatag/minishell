/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_creator_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:08:10 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 22:04:01 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*new_node(char *value, t_token_type type)
{
	t_token	*new_token;
	int		i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\"' || value[i] == '\'')
			break ;
		i++;
	}
	new_token = safe_malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("error malloc\n");
		return (NULL);
	}
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	add_node_back(t_token **list_token, t_token *new_token)
{
	t_token	*head;

	if (!list_token || *list_token == NULL)
	{
		*list_token = new_token;
		return ;
	}
	head = *list_token;
	while (head->next != NULL)
		head = head->next;
	head->next = new_token;
	new_token->prev = head;
}

void	add_token(t_token **token, char *str, int count)
{
	t_token	*new_token;

	if ((check_wildcard(str) && ((*token) == NULL || ((*token)
					&& !((*token)->type & REDIRECTION)))))
		listfile(str, token);
	else
	{
		new_token = new_node(str, return_type(str, count));
		if (!new_token)
			return ;
		add_node_back(token, new_token);
	}
}
