#include "../include/minishell.h"
int    builtin_env()
{
    t_env *ptr_envs;

    ptr_envs = g_env;
    while (ptr_envs)
    {
        printf("%s=%s\n", ptr_envs->key, ptr_envs->value);
        ptr_envs = ptr_envs->next;
    }
    return (0);
}