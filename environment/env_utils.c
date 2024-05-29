#include "../include/minishell.h"
void add_env_node_to_list(t_env *new)
{
    t_env *temp;

    if (global.env == NULL)
        global.env = new;
    else
    {
        temp = global.env;
        while (temp->next)
            temp = temp->next;
        temp->next = new;
        new->prev = temp;
    }
}

char *create_value(char *value_start)
{
    char *value;

    value = remove_quotes(value_start);
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

    if (!delimiter)
        key_len = ft_strlen(env);
    else
        key_len = delimiter - env;
    key = safe_malloc((key_len + 1) * sizeof(char));
    if (!key)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_strlcpy(key, env, key_len + 1);
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

void add_envp(char *env)
{
    t_env *new;

    new = create_env_node(env);
    if (!new)
        return;
    add_env_node_to_list(new);
}
