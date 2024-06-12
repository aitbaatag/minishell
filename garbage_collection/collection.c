/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:58:57 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:23:03 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_garbage(t_garbage **list)
{
	t_garbage	*current;
	t_garbage	*next;

	current = *list;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*list = NULL;
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

t_garbage	*new_garbage_node(void *ptr)
{
	t_garbage	*new_node;

	new_node = malloc(sizeof(t_garbage));
	if (!new_node)
		return (NULL);
	new_node->ptr = ptr;
	new_node->next = NULL;
	return (new_node);
}

void	add_garbage_node(t_garbage **list, t_garbage *new_node)
{
	t_garbage	*current;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
	}
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	*safe_malloc(size_t size)
{
	void		*ptr;
	t_garbage	*new_node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = new_garbage_node(ptr);
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	add_garbage_node(&global.garbage_list, new_node);
	return (ptr);
}
