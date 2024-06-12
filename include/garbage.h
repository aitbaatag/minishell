/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:46:46 by asadiqui          #+#    #+#             */
/*   Updated: 2024/06/12 19:14:29 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include "minishell.h"

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}	t_garbage;

void		free_garbage(t_garbage **list);
t_garbage	*new_garbage_node(void *ptr);
void		add_garbage_node(t_garbage **list, t_garbage *new_node);
void		*safe_malloc(size_t size);
void		free_token_list(t_token *head);

#endif