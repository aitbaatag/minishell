#include "../include/minishell.h"

t_global	global;

int main(int argc, char *argv[], char *envp[])
{
    t_data *data;
    t_global global;
	t_env	*homedir;

	//if (isatty(STDIN_FILENO))
	//	welcome();
    global.env = NULL;
	global.homedir = NULL;
    global.old_stdout = dup(STDOUT_FILENO);
    global.old_stdin = dup(STDIN_FILENO);
    data = safe_malloc(sizeof(data));

    (void)argv;
    (void)argc;
    if (argc > 1)
    {
        perror("error run programe ./minishell without any args\n");
        exit (EXIT_FAILURE);
    }
    set_env(envp);
    global.flag = 0;
	homedir = find_env_var(global.env, "HOME");
	if (homedir)
		global.homedir = homedir->value;
    while (1)
    {
		// signal(SIGINT, sigint_handler);
		// signal(SIGQUIT, SIG_IGN);
        data->line = readline("\033[1;32mminishell@1337:~$ \033[0m");
		// if (data->line == NULL)
		// 	eof_handler();
        add_history(data->line);
        data->tokens = tokenization(data->line);
        data->tree = build_tree(&data->tokens);
        executer(data->tree);
        global.flag = 0;
        free (data->line);
    }
}
