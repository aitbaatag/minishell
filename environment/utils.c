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
char *create_value(char *value_start)
{
    char *value;
    value = strdup(value_start);
    if (!value)
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    return value;
}

char *create_key(char *env, char *delimiter)
{
    size_t key_len;
    char *key;

    key_len = delimiter - env;
    key = safe_malloc((key_len + 1) * sizeof(char));
    if (!key)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_strlcpy(key, env, key_len);
    return key;
}

t_env *create_env_node(char *env)
{
    char *delimiter;
    t_env *new;

    delimiter = ft_strchr(env, '=');
    if (!delimiter)
        return NULL;
    new = safe_malloc(sizeof(t_env));
    if (!new)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new->key = create_key(env, delimiter);
    new->value = create_value(delimiter + 1);
    new->next = NULL;
    new->prev = NULL;
    return new;
}

void add_envp(char *env, t_env **envs)
{
    t_env *new;
    new = create_env_node(env);
    if (!new)
        return;
    add_env_node_to_list(envs, new);
}
