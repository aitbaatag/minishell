#include "../include/minishell.h"
size_t get_envp_size(char **envp, t_env *envs, int i)
{
    size_t size = 0;
    t_env *ptr_env;

    ptr_env = envs;
    if (i == 0)
    {
        while (envp[size])
            size++;
    }
    else if (i == 1)
    {
        while (ptr_env)
        {
            ptr_env = ptr_env->next;
            size++;
        }
    }
    return size;
}

