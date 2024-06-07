#include "../include/minishell.h"

void	clean(t_garbage *garbage)
{
	t_garbage	*tmp;
	while (garbage)
	{
		tmp = garbage;
		free(garbage->address);
		garbage = garbage->next;
		if (garbage->next)
			free(tmp);
	}
}

void	*ft_malloc(size_t size, t_garbage *garbage)
{
	t_garbage	*current;
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	new->address = malloc(size);
	new->next = NULL;
	if (garbage == NULL)
	if (garbage == NULL)
	{
		garbage = new;
		return (new->address);
	}
	current = garbage;
	while (current)
		current = current->next;
	current = new;
	return (new->address);
}

// int	main()
// {
// 	t_garbage	garbage;
	
// 	// garbage = malloc(sizeof(t_garbage));
// 	garbage.address = NULL;
// 	garbage.next = NULL;
// 	char	*to_free0 = ft_malloc(sizeof(char) * 6, &garbage);
// 	char	*to_free1 = ft_malloc(sizeof(char) * 5, &garbage);
// 	while (garbage.next)
// 	{
// 		printf("address: %p\n", garbage.address);
// 		garbage = *(garbage.next);
// 	}
// 	to_free0 = "hello";
// 	to_free1 = "hell";
// 	printf("%s_%s\n", to_free0, to_free1);
// 	clean(&garbage);
// 	return (0);
// }
