/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:58:05 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:10:05 by kait-baa         ###   ########.fr       */
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

int	run_subshell(t_tree *subshell)
{
	t_grp_exec	*group_root;
	int			orig_stdin;
	int			orig_stdout;

	group_root = (t_grp_exec *)subshell;
	if (group_root->outer_redir)
	{
		save_and_restore_fd(&orig_stdin, &orig_stdout, 0);
		if (set_type_redi((t_tree *)group_root->outer_redir) != 0)
			return (get_exit_status());
	}
	ft_run_node(group_root->child);
	if (group_root->outer_redir)
	{
		save_and_restore_fd(&orig_stdin, &orig_stdout, 1);
	}
	return (get_exit_status());
}

int	run_redir(t_tree *tree)
{
	int	orig_stdin;
	int	orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	save_and_restore_fd(&orig_stdin, &orig_stdout, 0);
	set_exit_status(set_type_redi(tree));
	save_and_restore_fd(&orig_stdin, &orig_stdout, 1);
	return (get_exit_status());
}

void	parent(int *pipe_fd, int *status, pid_t *cpid)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(cpid[0], status, 0);
	waitpid(cpid[1], status, 0);
	if_exit_with_signal(status);
	set_exit_status(*status);
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
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit(ft_run_node(pipenode->left));
	}
	cpid[1] = fork();
	if (cpid[1] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exit(ft_run_node(pipenode->right));
	}
	parent(fd, &status, cpid);
	return (get_exit_status());
}

int	run_logic(t_tree *tree)
{
	t_logic	*logic;
	int		status;

	logic = (t_logic *)tree;
	status = 0;
	if (logic->type == AND)
	{
		status = ft_run_node(logic->left);
		if (status == EXIT_SUCCESS)
			status = ft_run_node(logic->right);
	}
	else if (logic->type == OR)
	{
		status = ft_run_node(logic->left);
		if (status != EXIT_SUCCESS && status != 130)
			status = ft_run_node(logic->right);
	}
	return (set_exit_status(status), get_exit_status());
}

int	handle_builtin(t_exec *exec, int orig_stdin, int orig_stdout)
{
	int	status;
	int	(*builtin)(t_exec * exec);

	builtin = is_builtin(exec->args[0]);
	if (builtin)
	{
		status = builtin(exec);
		save_and_restore_fd(&orig_stdin, &orig_stdout, 1);
		return (set_exit_status(status), get_exit_status());
	}
	return (-1);
}

int	handle_external_command(t_exec *exec)
{
	int		status;
	char	*path_cmd;

	signal(SIGINT, sigint_handler_nl);
	signal(SIGQUIT, sigint_handler_nl);
	path_cmd = get_path(exec->args[0]);
	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path_cmd, exec->args, env_to_array(global.env));
		cmd_notfound(exec->args[0]);
		free_garbage(&global.garbage_list);
		rl_clear_history();
		exit(get_exit_status());
	}
	signal(SIGQUIT, SIG_DFL);
	wait(&status);
	if_exit_with_signal(&status);
	return (status);
}

int	run_cmd(t_tree *tree)
{
	t_exec	*exec;
	int		status;
	int		orig_stdin;
	int		orig_stdout;

	exec = (t_exec *)tree;
	save_and_restore_fd(&orig_stdin, &orig_stdout, 0);
	if (set_type_redi((t_tree *)exec->child_redi) != 0)
	{
		save_and_restore_fd(&orig_stdin, &orig_stdout, 1);
		return (get_exit_status());
	}
	expand(exec->args, 0);
	if (!exec->args[0])
		return (set_exit_status(0), get_exit_status());
	status = handle_builtin(exec, orig_stdin, orig_stdout);
	if (status != -1)
		return (status);
	status = handle_external_command(exec);
	save_and_restore_fd(&orig_stdin, &orig_stdout, 1);
	set_exit_status(status);
	return (status);
}
