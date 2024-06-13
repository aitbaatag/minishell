/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:39:59 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 23:06:39 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parent(int *pipe_fd, int *status, pid_t *cpid)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(cpid[0], status, 0);
	waitpid(cpid[1], status, 0);
	if_exit_with_signal(status);
	set_exit_status(*status);
}

void	run_left_child_process(int *fd, t_pipe *pipenode)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	set_exit_status(ft_run_node(pipenode->left));
	free_garbage(&g_global.garbage_list);
	exit(get_exit_status());
}

void	run_right_child_process(int *fd, t_pipe *pipenode)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	set_exit_status(ft_run_node(pipenode->right));
	free_garbage(&g_global.garbage_list);
	exit(get_exit_status());
}

int	run_pipe(t_tree *tree)
{
	int		fd[2];
	pid_t	cpid[2];
	int		status;
	t_pipe	*pipenode;

	signal(SIGINT, sigint_handler_exit);
	signal(SIGQUIT, sigint_handler_exit);
	pipenode = (t_pipe *)tree;
	pipe(fd);
	cpid[0] = fork();
	if (cpid[0] == 0)
		run_left_child_process(fd, pipenode);
	cpid[1] = fork();
	if (cpid[1] == 0)
		run_right_child_process(fd, pipenode);
	parent(fd, &status, cpid);
	return (get_exit_status());
}
