/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:39:59 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 20:48:26 by asadiqui         ###   ########.fr       */
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

void	run_child_process(int *fd, int std_fd, t_tree *node, int close_fd,
		int dup_fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(fd[close_fd]);
	dup2(fd[dup_fd], std_fd);
	close(fd[dup_fd]);
	set_exit_status(ft_run_node(node));
	free_garbage(&global.garbage_list);
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
		run_child_process(fd, STDOUT_FILENO, pipenode->left, 0, 1);
	cpid[1] = fork();
	if (cpid[1] == 0)
		run_child_process(fd, STDIN_FILENO, pipenode->right, 1, 0);
	parent(fd, &status, cpid);
	return (get_exit_status());
}
