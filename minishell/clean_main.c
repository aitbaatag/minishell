#include "../include/minishell.h"
t_env *g_env = NULL;

int main(int argc, char *argv[], char *envp[])
{
    t_data *data;
    char **value;
    t_env *g_env;

    g_env = NULL;
    value =ft_split("export var=jjjjjjjjjjjjjjjjjjjjjjjjj", ' ');
    data = safe_malloc(sizeof(data));

    (void)argv;
    (void)argc;
    if (argc > 1)
    {
        perror("error run programe ./minishell without any args\n");
        exit (EXIT_FAILURE);
    }
    set_env(envp);
    while (1)
    {
        data->line = readline("minishell@1337:~$ ");
        data->tokens = tokenization(data->line);
        if (!ft_strcmp("export", "export"))
            export_env_var(value);

        // data->root = build_tree(&data->tokens);
        //start_execute(data->root);
    }
}   