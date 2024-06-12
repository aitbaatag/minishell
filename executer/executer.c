/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:58:14 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 20:54:34 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	save_and_restore_fd(int *orig_stdin, int *orig_stdout, int action)
{
	if (action == 0)
	{
		*orig_stdin = dup(STDIN_FILENO);
		*orig_stdout = dup(STDOUT_FILENO);
	}
	else if (action == 1)
	{
		dup2(*orig_stdin, STDIN_FILENO);
		dup2(*orig_stdout, STDOUT_FILENO);
		close(*orig_stdin);
		close(*orig_stdout);
	}
}

int	ft_run_node(t_tree *tree)
{
	if (tree->type == PIPE)
		return (run_pipe(tree));
	else if (tree->type == SUBSHELL)
		return (run_subshell(tree));
	else if (tree->type == EXEC)
		return (run_cmd(tree));
	else if (tree->type == AND || tree->type == OR)
		return (run_logic(tree));
	else if (tree->type == HEREDOC || tree->type == INPUT_REDIRECTION || \
		tree->type == APPEND_REDIRECTION
		|| tree->type == OUTPUT_REDIRECTION)
		return (run_redir(tree));
	return (EXIT_FAILURE);
}

void	executer(t_tree *tree)
{
	if (!tree)
		return ;
	set_exit_status(ft_run_node(tree));
}
