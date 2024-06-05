#include "../include/minishell.h"

// int run_subshell(t_tree *subshell)
// {
// 	t_grp_exec *group_root;

// 	group_root = (t_grp_exec *)subshell;
// 	if (group_root->outer_redir)
// 	{
// 		set_type_redi((t_tree *)group_root->outer_redir);
// 	}
// 	ft_run_node(group_root->child);
// 	if (group_root->outer_redir)
// 	{
// 		dup2(global.old_stdin, STDIN_FILENO);
// 		dup2(global.old_stdout, STDOUT_FILENO);
// 	}

// 	return (get_exit_status());
// }
int run_subshell(t_tree *subshell)
{
	t_grp_exec *group_root;
	int orig_stdin;
	int orig_stdout;

	group_root = (t_grp_exec *)subshell;
	if (group_root->outer_redir)
	{
		// Save original stdin and stdout
		orig_stdin = dup(STDIN_FILENO);
		orig_stdout = dup(STDOUT_FILENO);
		if (set_type_redi((t_tree *)group_root->outer_redir) != 0)
			return (get_exit_status());
	}
	ft_run_node(group_root->child);
	if (group_root->outer_redir)
	{
		// Restore original stdin and stdout
		dup2(orig_stdin, STDIN_FILENO);
		dup2(orig_stdout, STDOUT_FILENO);
	}
	return (get_exit_status());
}
int run_redir(t_tree *tree)
{
	int orig_stdin;
	int orig_stdout;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	set_exit_status(set_type_redi(tree));
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
	return (get_exit_status());
}

// int run_pipe(t_tree *tree)
// {
// 	int fd[2];
// 	pid_t cpid;
// 	t_pipe *pipenode;

// 	pipenode = (t_pipe *)tree;
// 	pipe(fd);
// 	cpid = fork();
// 	if (cpid == 0) // Child process
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		ft_run_node(pipenode->left);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else // Parent process
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		wait(NULL);
// 		ft_run_node(pipenode->right);
// 		dup2(global.old_stdin, STDIN_FILENO);
// 		dup2(global.old_stdout, STDOUT_FILENO);

// 	}
// 	return (get_exit_status());
// }
void parent(int *pipe_fd, int *status, int *orig_fd, pid_t *cpid)
{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(cpid[0], status, 0);
		waitpid(cpid[1], status, 0);
		dup2(orig_fd[0], STDIN_FILENO);
		dup2(orig_fd[1], STDOUT_FILENO);
		close(orig_fd[0]);
		close(orig_fd[1]);
		// printf("status: %d\n", *status);
		set_exit_status(*status % 255);
		// printf ("%d\n",  WEXITSTATUS(*status));
}
int run_pipe(t_tree *tree)
{
	int fd[2];
	pid_t cpid[2];
	// pid_t cpid2;
	int status;
	t_pipe *pipenode;
	int orig_fd[2];

	orig_fd[1] = dup(STDOUT_FILENO);
	orig_fd[0] = dup(STDIN_FILENO);
	pipenode = (t_pipe *)tree;
	pipe(fd);
	cpid[0] = fork();
	if (cpid[0] == 0) // Child process 1
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit(ft_run_node(pipenode->left));
	}
	cpid[1] = fork();
	if (cpid[1] == 0) // Child process 2
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exit(ft_run_node(pipenode->right));
	}
	parent(fd, &status, orig_fd, cpid);
	return (get_exit_status());
}

int run_logic(t_tree *tree)
{
	t_logic *logic;
	int status;

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
		if (status != EXIT_SUCCESS)
			status = ft_run_node(logic->right);
	}
	return (set_exit_status(status), get_exit_status());
}

// int run_cmd(t_tree *tree)
// {
// 	t_exec *exec;
// 	int status;
// 	int (*builtin)(t_exec *exec);

// 	exec = (t_exec *)tree;
// 	if (set_type_redi((t_tree *)exec->child_redi) != 0)
// 		return (get_exit_status());
// 	expand(exec);
// 	builtin = is_builtin(exec->args[0]);
// 	if (builtin)
// 		return (set_exit_status(builtin(exec)), get_exit_status());
// 	if (fork() == 0)
// 	{
// 		execve(get_path(exec->args[0]), exec->args, env_to_array(global.env));
// 		cmd_notfound(exec->args[0]);
// 		// collect_garbage();
// 		exit(get_exit_status());
// 	}
// 	wait(&status);
// 	if (WIFEXITED(status))
// 		status = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		status = WTERMSIG(status) + 128;
// 	set_exit_status(status);
//     dup2(global.old_stdin, STDIN_FILENO);
// 	dup2(global.old_stdout, STDOUT_FILENO);
//     // close(orig_stdin);
//     // close(orig_stdout);
// 	return (status);
// }

int run_cmd(t_tree *tree)
{
	t_exec *exec;
	int status;
	int (*builtin)(t_exec *exec);
	int orig_stdin;
	int orig_stdout;

	exec = (t_exec *)tree;
	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	if (set_type_redi((t_tree *)exec->child_redi) != 0)
		return (get_exit_status());
	expand(exec->args);
	builtin = is_builtin(exec->args[0]);
	if (builtin)
	{
		status = builtin(exec);
		dup2(orig_stdin, STDIN_FILENO);
		dup2(orig_stdout, STDOUT_FILENO);
		return (set_exit_status(status), get_exit_status());
	}
	if (fork() == 0)
	{
		execve(get_path(exec->args[0]), exec->args, env_to_array(global.env));
		cmd_notfound(exec->args[0]);
		// collect_garbage();
		exit(get_exit_status());
	}
	wait(&status);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	set_exit_status(status);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
	return (status);
}