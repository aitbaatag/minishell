#include "../include/minishell.h"
int	get_status(t_tree *tree)
{
	if (tree->type == PIPE)
		return (run_pipe(tree));
	else if (tree->type == SUBSHELL)
		return (run_subshell(tree));
	else if (tree->type == EXEC)
		return (run_cmd(tree));
	else if (tree->type & LOGICAL)
		return (run_logic(tree));
	else if (tree->type & REDIERCTION)
		return (run_redir(tree));
	return (EXIT_FAILURE);
}

void	executer(t_tree *tree)
{
	if (!tree)
		return ;
	set_exit_status(get_status(tree));
}