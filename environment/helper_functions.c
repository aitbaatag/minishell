#include "../include/minishell.h"

t_env *find_env_var(t_env *envs, char *key)
{
    t_env *current;
    int i;

    i = 0;
    while (key[i])
    {
        if (key[i] == '+' && key[i + 1] == '\0')
            break;
        i++;
    }
    current = envs;
    while (current)
    {
        if (ft_strncmp(current->key, key, i) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return (NULL);
}