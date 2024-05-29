#include "../include/minishell.h"
int builtin_unset(char *key)
{
    t_env *key_node;

    key_node = find_env_var(g_env, key);

    if (key_node)
    {
        if (key_node->prev)
            key_node->prev->next = key_node->next;
        else
            g_env = key_node->next;
        if (key_node->next)
            key_node->next->prev = key_node->prev;
        free(key_node->key);
        free(key_node->value);
        free(key_node);
    }
    return (0);
}