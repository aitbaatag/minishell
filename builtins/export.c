#include "../include/minishell.h"
void bubble_sort_env(char **env_array, size_t size)
{
    size_t i;
    size_t j;
    char *temp;
    int swapped;

    i = 0;
    while (i < size - 1)
    {
        j = 0;
        swapped = 0;
        while (j < size - i - 1)
        {
            if (ft_strcmp((const char *)env_array[j], (const char *)env_array[j + 1]) > 0)
            {
                temp = env_array[j];
                env_array[j] = env_array[j + 1];
                env_array[j + 1] = temp;
                swapped = 1;
            }
            j++;
        }
        if (!swapped)
            break;
        i++;
    }
}
void print_sorted_env(t_env *envs)
{
    char **env_array;
    size_t size;
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    env_array = convert_env_list_to_array(envs);
    size = get_envp_size(NULL, envs, 1);
    bubble_sort_env(env_array, size - 1);
    while (i < size)
    {
        j = 0;
        printf("declare -x ");
        while (env_array[i][j] != '=')
            printf ("%c", env_array[i][j++]);
        printf ("=\"");
        while (env_array[i][j])
            printf ("%c", env_array[i][++j]);
        printf ("\"\n");
        free(env_array[i]);
        i++;
    }
    free(env_array);
}
void add_var_to_envs_or_app_modif_exis(char *arg)
{
    char *key;
    t_env *current;
    int i;
    int flag;
    char *value;
    char *new_value;
    char *delimiter;

    flag = 0;
    i = 0; 
    delimiter = ft_strchr(arg, '=');
    if (delimiter)
        value = create_value(delimiter + 1);
    key = create_key(arg, delimiter);
    current = find_env_var(g_env, key);
    if (current)
    {
        while (arg[i])
        {
            if (arg[i] == '+' && arg[i + 1] == '=')
            {
                flag = 1;
                break;
            }
            i++;
        }
        if (flag == 1)
        {
            new_value = ft_strjoin(current->value, value);
            free (current->value);   
            current->value = new_value;
        }
        else
        {
            free(current->value);
            current->value = ft_strdup(value);
        }
    }
    else
        add_envp(arg);
    free (key);
    free (value);   
}
void export_env_var(char **args)
{
    int i;
    t_env *envs;

    envs = g_env;
    i = 1;
    if (args[1] == NULL)
        print_sorted_env(envs);
    else
    {
        while (args[i])
        {
            add_var_to_envs_or_app_modif_exis(args[i]);
            i++;
        }
    }
}