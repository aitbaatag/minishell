#include "../include/minishell.h"
int    builtin_env(t_exec *exec)
{
    t_env *ptr_envs;
    (void)exec;

    ptr_envs = global.env;
    while (ptr_envs)
    {
        printf("%s", ptr_envs->key);
        if (ptr_envs->value)
            printf("=%s\n",ptr_envs->value);
        else
            printf ("\n");
        ptr_envs = ptr_envs->next;
    }
    return (0);
}