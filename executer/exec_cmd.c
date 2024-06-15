/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:53:45 by asadiqui          #+#    #+#             */
/*   Updated: 2024/06/14 20:30:52 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	cmd_exit_126(char *cmd)
{
	struct stat	info;

	stat(cmd, &info);
	if (S_ISDIR(info.st_mode))
	{
		ft_putstr_fd(RED ": Is a directory\n" CLOSE, 2);
		set_exit_status(126);
		return ;
	}
	if (access(cmd, R_OK | X_OK) == -1)
	{
		ft_putstr_fd(RED "Permission denied\n" CLOSE, 2);
		set_exit_status(126);
		return ;
	}
	return ;
}

void	cmd_notfound(char *cmd)
{
	int	i;
	int	backslash;

	ft_putstr_fd(cmd, 2);
	if (access(cmd, F_OK) == -1)
	{
		i = 0;
		backslash = 0;
		while (cmd[i])
			if (cmd[i++] == '/')
				backslash = 1;
		if (backslash)
			ft_putstr_fd(RED ": No such file or directory\n" CLOSE, 2);
		else
			ft_putstr_fd(RED ": command not found\n" CLOSE, 2);
		set_exit_status(127);
		return ;
	}
	return (cmd_exit_126(cmd));
}

int	handle_builtin(t_exec *exec, int orig_stdin, int orig_stdout)
{
	int	status;
	int	(*builtin)(t_exec *exec);

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
		execve(path_cmd, exec->args, env_to_array(g_global.env));
		cmd_notfound(exec->args[0]);
		free_garbage(&g_global.garbage_list);
		exit(get_exit_status());
	}
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
	exec->args = expand(exec->args, 0);
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
