#ifndef GARBAGE_H
# define GARBAGE_H

#include "minishell.h"

typedef	struct s_garbage
{
	void				*address;
	struct s_garbage	*next;
}	t_garbage;

void	*ft_malloc(size_t size, t_garbage *garbage);
void	clean(t_garbage *garbage);

#endif