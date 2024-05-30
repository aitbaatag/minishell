#include "../include/minishell.h"

int	run_subshell(t_tree *subshell)
{
	(void)subshell;
    return (0);
}

int	run_redir()
{
	return (0);
}
int run_pipe(t_tree *tree)
{
    int fd[2];
    int status;
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
        get_status(pipenode->right);
		dup2(copy_fdin, STDIN_FILENO);
		dup2(copy_fd, STDOUT_FILENO);
        while (wait(&status) != -1)
			;
        close(copy_fdin);
        close(copy_fd);
    }
    return 0;
}
int	run_logic(t_tree *tree)
{
	t_logic	*logic;
	int		status;
	
	logic = (t_logic *)tree;
	status = 0;
	// execute both commands if 1st is true
	if (logic->type == AND)
	{
		status = get_status(logic->left);
		if (status == EXIT_SUCCESS)
			status = get_status(logic->right);
	}
	// execute 2nd only if 1st if false
	else if (logic->type == OR)
	{
		status = get_status(logic->left);
		if (status == EXIT_FAILURE)
			status = get_status(logic->right);
	}
	set_exit_status(status);
	return (status);
}

int     run_cmd(t_tree *tree)
{
	t_exec	*exec;
	int		status;
	int		(*builtin)(t_exec *exec);	// a pointer to the builtin function

	exec = (t_exec *)tree;
	// if the command is emtpy == space/tab ...
		// return (set_exit_status(0), 0);
	//	exec->env = get_env_list();
	//	expand((t_tree *)exec);
	// if the command is emtpy == space/tab ... (after expand)
		// return (set_exit_status(0), 0);
	builtin = is_builtin(exec->args[0]);
	if (builtin)
		return (set_exit_status(builtin(exec)), get_exit_status());
	status = check_cmd(exec); // check weither to run from path or run an executable
	if (status != 0)
		return (status); // return that exit_status on failure
	// handle signals
	exec->env = global.env;
	if (fork() == 0)	// execute child
	{
		// char **array = env_to_array(exec->env);
		// printf("hughosuhgo\n");
		execve(get_path(exec->args[0]), exec->args, env_to_array(exec->env));
		// printf("hughosuhgo\n");
		printf("\033[0;31m%s\n\033[0m", exec->args[0]); // error/perror?
		set_exit_status(127);
		// collect_garbage();
		exit(get_exit_status());
	}
	// waitpid
	wait(&status);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	// When a command terminates on a fatal signal whose number is N,
	// Bash uses the value 128+N as the exit status.
		status = WTERMSIG(status) + 128;
	// set_env(exec->args); modify the environment if applicable
	set_exit_status(status);
	// handle readline buffer
	return (status);
}