#include "../include/minishell.h"

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
	else if (tree->type == HEREDOC || tree->type == INPUT_REDIRECTION ||
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