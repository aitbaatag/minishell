#include "../include/minishell.h"
char **copy_envp(char **envp)
{
    size_t size;
    size_t i;

    i = 0;
    size = get_envp_size(envp);
    char **my_envp = (char **)malloc((size + 1) * sizeof(char *));

    if (!my_envp)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (i < size)
    {
        my_envp[i] = ft_strdup(envp[i]);
        if (!my_envp[i])
        {
            perror("ft_strdup");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    my_envp[size] = NULL;
    return my_envp;
}
t_env *set_env(char **envp)
{
    t_env *envs = NULL;
    int i = 0;

    while (envp[i])
    {
        add_envp(envp[i], &envs);
        i++;
    }
    return envs;
}
