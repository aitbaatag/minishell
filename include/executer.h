/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:46:40 by asadiqui          #+#    #+#             */
/*   Updated: 2024/06/12 23:08:31 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

typedef struct s_tree	t_tree;

// #define _GNU_SOURCE // for pipe ?
int		run_pipe(t_tree *tree);
int		run_logic(t_tree *tree);
int		run_cmd(t_tree *tree);
int		run_subshell(t_tree *subshell);
int		run_redir(t_tree *tree);

int		ft_run_node(t_tree *tree);
int		get_exit_status(void);
void	set_exit_status(int status);
void	if_exit_with_signal(int *status);
void	executer(t_tree *tree);

// utils
void	cmd_notfound(char *cmd);
char	*get_path(char *command);

int		set_type_redi(t_tree *redi);
int		handle_redir_input(t_redi_exec *redi);
int		handle_redir_output(t_redi_exec *redi);
void	save_and_restore_fd(int *orig_stdin, int *orig_stdout, int action);

#endif