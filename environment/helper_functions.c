#include "../include/minishell.h"

t_env *find_env_var(t_env *envs, char *key)
{
    t_env *current;

    current = envs;
    while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key) + 1) == 0)
		{
            return current;
        }
        current = current->next;    
    }
    return (NULL);
}