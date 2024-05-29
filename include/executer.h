#ifndef EXECUTER_H
#define EXECUTER_H

#include "minishell.h"

typedef struct s_tree t_tree;

// #define _GNU_SOURCE // for pipe ?
int	run_pipe(t_tree *tree);
int	run_logic(t_tree *tree);
int	run_cmd(t_tree *tree);
int	run_subshell(t_tree *subshell);
int	run_redir();

int		get_status(t_tree *tree);
int		get_exit_status(void);
void	set_exit_status(int status);
void	executer(t_tree *tree);

// utils
int		check_cmd(t_exec *exec);
char	*get_path(char *command);
void	free_it(char **split_path);

#endif