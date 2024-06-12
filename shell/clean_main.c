/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:06:58 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:48:57 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_global	global;
int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	(void)argv;
	global.env = NULL;
	global.garbage_list = NULL;
	data = safe_malloc(sizeof(t_data));
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
		if (data->line[0])
			add_history(data->line);
		*heredoc_signaled() = -1;
		data->tokens = tokenization(data->line);
		if (analyze_syntax(data->tokens) && ambiguous_redirect(data->tokens))
		{
			data->tree = build_tree(&data->tokens);
			executer(data->tree);
		}
		add_garbage_node(&global.garbage_list, new_garbage_node(data->line));
	}
	free_garbage(&global.garbage_list);
}

// rl_clear_history()