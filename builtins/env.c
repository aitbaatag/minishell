#include "../include/minishell.h"
int    builtin_env(t_exec *exec)
{
    t_env *ptr_envs;

    ptr_envs = global.env;
    if (exec->args[1] != NULL)
    {
        printf("env: ’%s’: No such file or directory\n", exec->args[1]);
        return (set_exit_status(127), get_exit_status());
    }
    while (ptr_envs)
    {
        printf("%s", ptr_envs->key);
        if (ptr_envs->value)
            printf("=%s\n",ptr_envs->value);
        else
            printf ("\n");
        ptr_envs = ptr_envs->next;
    }
    return (set_exit_status(0), get_exit_status());
}
