#include "../include/minishell.h"
void	rebuild_envp(t_env *envs)
{
    t_env *ptr_envs;
    char **env_array;
    int i;
    size_t size;

    size = get_envp_size(NULL, envs, 1);
    i = 0;
    env_array = safe_malloc((size + 1)* sizeof(char *));
    env_array[size] = NULL;
    ptr_envs = envs;
    while (ptr_envs)
    {
        env_array[i] = ft_strjoin(ptr_envs->key, "=");
        if (ptr_envs->value)
            env_array[i] = ft_strjoin(ptr_envs->key, ptr_envs->value);
        ptr_envs = ptr_envs->next;
    }
}