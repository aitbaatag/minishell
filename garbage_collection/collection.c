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

void	*safe_malloc(size_t size, t_garbage **list)
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
	add_garbage_node(list, new_node);
	return (ptr);
}
// #include <stdio.h>
// #include <string.h>

// // Include the garbage collection functions here

// int main() {
//     t_garbage *garbage_list = NULL;

//     char *str1 = (char *)safe_malloc(100 * sizeof(char), &garbage_list);
//     char *str2 = (char *)safe_malloc(50 * sizeof(char), &garbage_list);

//     if (!str1 || !str2) {
//         fprintf(stderr, "Memory allocation failed\n");
//         free_garbage(&garbage_list);
//         return (1);
//     }

//     strcpy(str1, "Hello, world!");
//     strcpy(str2, "Goodbye, world!");

//     printf("%s\n", str1);
//     printf("%s\n", str2);

//     // Free all allocated memory
//     free_garbage(&garbage_list);

//     return (0);
// }
