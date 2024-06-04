#include "../include/minishell.h"

// int run_subshell(t_tree *subshell)
// {
// 	t_grp_exec *group_root;

// 	group_root = (t_grp_exec *)subshell;
// 	if (group_root->outer_redir)
// 	{
// 		set_type_redi((t_tree *)group_root->outer_redir);
// 	}
// 	get_status(group_root->child);
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
	get_status(group_root->child);
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
// 		get_status(pipenode->left);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else // Parent process
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		wait(NULL);
// 		get_status(pipenode->right);
// 		dup2(global.old_stdin, STDIN_FILENO);
// 		dup2(global.old_stdout, STDOUT_FILENO);

// 	}
// 	return (get_exit_status());
// }
int run_pipe(t_tree *tree)
{
	int fd[2];
	pid_t cpid;
	t_pipe *pipenode;
	int copy_fd;
	int copy_fdin;

	copy_fd = dup(STDOUT_FILENO);
	copy_fdin = dup(STDIN_FILENO);
	pipenode = (t_pipe *)tree;
	pipe(fd);
	cpid = fork();
	if (cpid == 0) // Child process
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		get_status(pipenode->left);
		exit(EXIT_SUCCESS);
	}
	else // Parent process
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
		get_status(pipenode->right);
		dup2(copy_fdin, STDIN_FILENO);
		dup2(copy_fd, STDOUT_FILENO);
		close(copy_fdin);
		close(copy_fd);
	}
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
        status = get_status(logic->left);
        if (status == EXIT_SUCCESS)
            status = get_status(logic->right);
    }
    else if (logic->type == OR)
    {
        status = get_status(logic->left);
        if (status != EXIT_SUCCESS)
            status = get_status(logic->right);
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
	expand(exec);
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