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

int		ft_run_node(t_tree *tree);
int		get_exit_status(void);
void	set_exit_status(int status);
void	executer(t_tree *tree);

// utils
void	expand(char **args);
void	cmd_notfound(char *cmd);
char	*get_path(char *command);
void	free_it(char **split_path);


int	set_type_redi(t_tree *redi);
int handle_redir_input(t_redi_exec *redi);
int handle_redir_output(t_redi_exec *redi);
int save_and_redirect(int old_fd, int new_fd);
void restore_fd(int old_fd, int saved_fd);

#endif