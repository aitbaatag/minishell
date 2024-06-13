/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:06:58 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/13 04:50:33 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_global	global;

static void	parse_and_execute(t_data *data)
{
	data->tokens = tokenization(data->line);
	if (analyze_syntax(data->tokens) && ambiguous_redirect(data->tokens))
	{
		data->tree = build_tree(&data->tokens);
		executer(data->tree);
	}
	add_garbage_node(&global.garbage_list, new_garbage_node(data->line));
}

static void	read_input(t_data *data)
{
	data->line = readline(GREEN PROMPT CLOSE);
	if (data->line == NULL)
		eof_handler();
	if (data->line[0])
		add_history(data->line);
	*heredoc_signaled() = -1;	
}

static void	init_signals()
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		ft_putstr_fd("signal error\n", STDERR_FILENO);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_putstr_fd("signal error\n", STDERR_FILENO);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	(void)argc;
	(void)argv;
	global.env = NULL;
	global.garbage_list = NULL;
	global.y = 0;
	data = safe_malloc(sizeof(t_data));
	// if (argc > 1)
	// {
	// 	perror("error run programe ./minishell without any args\n");
	// 	exit(EXIT_FAILURE);
	// }
	set_env(envp);
	while (1)
	{
		init_signals();
		read_input(data);
		parse_and_execute(data);
	}
}
