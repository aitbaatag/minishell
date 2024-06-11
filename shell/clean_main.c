#include "../include/minishell.h"

t_global	global;
int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	//if (isatty(STDIN_FILENO))
	//	welcome();
	global.env = NULL;
	global.garbage_list = NULL;
	global.fd = dup(0);
	global.break_2 = 0;
	data = safe_malloc(sizeof(t_data));
	(void)argv;
	(void)argc;
	if (argc > 1)
	{
		perror("error run programe ./minishell without any args\n");
		exit(EXIT_FAILURE);
	}
	set_env(envp);
	while (1)
	{
		if (signal(SIGINT, sigint_handler) == SIG_ERR)
			ft_putstr_fd("signal error\n", STDERR_FILENO);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			ft_putstr_fd("signal error\n", STDERR_FILENO);
		data->line = readline("\033[1;32mminishell@1337:~$ \033[0m");
		if (data->line == NULL)
			eof_handler();
		add_history(data->line);
		data->tokens = tokenization(data->line);
		if (analyze_syntax(data->tokens) == true)
		{
			data->tree = build_tree(&data->tokens);
			executer(data->tree);
		}
		add_garbage_node(&global.garbage_list ,new_garbage_node(data->line));
	}
	free_garbage(&global.garbage_list);
}

// rl_clear_history()