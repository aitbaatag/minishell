/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:06:58 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/14 12:06:31 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_global	g_global;

static void	parse_and_execute(t_data *data)
{
	data->tokens = tokenization(data->line);
	if (analyze_syntax(data->tokens) && ambiguous_redirect(data->tokens))
	{
		data->tree = build_tree(&data->tokens);
		executer(data->tree);
	}
	add_garbage_node(&g_global.garbage_list, new_garbage_node(data->line));
}

static void	read_input(t_data *data)
{
	char	*prompt;

	prompt = get_prompt();
	data->line = readline(prompt);
	if (data->line == NULL)
		eof_handler();
	if (data->line[0])
		add_history(data->line);
	*heredoc_signaled() = -1;
}

static void	init_signals(void)
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
	g_global.env = NULL;
	g_global.garbage_list = NULL;
	g_global.to_split = 0;
	data = safe_malloc(sizeof(t_data));
	set_env(envp);
	while (1)
	{
		init_signals();
		read_input(data);
		parse_and_execute(data);
	}
}
