#include "../include/minishell.h"
char **env_to_array(t_env *envs)
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
            env_array[i] = ft_strjoin(env_array[i], ptr_envs->value);
        ptr_envs = ptr_envs->next;
        i++;
    }
    return (env_array);
}
// think again 
char **copy_envp(char **envp)
{
    size_t size;
    size_t i;
    char **my_envp;

    i = 0;
    size = get_envp_size(envp, NULL, 0);
    my_envp = (char **)malloc((size + 1) * sizeof(char *));
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
// convert arr env to list 
void set_env(char **envp)
{
    int		i;
	char	pwd[1024];

	i = 0;
	if (!envp || !*envp)
    {
		getcwd(pwd, sizeof(pwd));
		add_var_to_envs_or_app_modif_exis(ft_strjoin("PWD=", pwd));
        add_envp("SHLVL=1");
		add_envp("_=/usr/bin/env");
    }
    while (envp[i])
    {
        add_envp(envp[i]);
        i++;
    }
}
