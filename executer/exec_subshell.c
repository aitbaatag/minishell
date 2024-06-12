/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:44:54 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 19:44:55 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	run_subshell(t_tree *subshell)
{
	t_grp_exec	*group_root;
	int			orig_stdin;
	int			orig_stdout;
	int			pid;
	int			status;

	group_root = (t_grp_exec *)subshell;
	if (group_root->outer_redir)
	{
		save_and_restore_fd(&orig_stdin, &orig_stdout, 0);
		if (set_type_redi((t_tree *)group_root->outer_redir) != 0)
			return (get_exit_status());
	}
	pid = fork();
	if (pid == 0)
		exit(ft_run_node(group_root->child));
	waitpid(pid, &status, 0);
	if_exit_with_signal(&status);
	set_exit_status(status);
	if (group_root->outer_redir)
		save_and_restore_fd(&orig_stdin, &orig_stdout, 1);
	return (get_exit_status());
}
