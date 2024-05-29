#include "../include/minishell.h"

t_global	global;

int main(int argc, char *argv[], char *envp[])
{
    t_data *data;
    t_global global;

	// global = malloc(sizeof(t_global));
    global.env = NULL;
    global.status = 0;
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
        data->line = readline("\033[1;32mminishell@1337:~$ \033[0m");
        data->tokens = tokenization(data->line);
        data->tree = build_tree(&data->tokens);
        executer(data->tree);
    }
}