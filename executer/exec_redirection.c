/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:58:12 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/13 02:03:06 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	run_redir(t_tree *tree)
{
	int	orig_stdout;
	int	orig_stdin;

	orig_stdin = dup(STDIN_FILENO);
	orig_stdout = dup(STDOUT_FILENO);
	save_and_restore_fd(&orig_stdin, &orig_stdout, 0);
	set_exit_status(set_type_redi(tree));
	save_and_restore_fd(&orig_stdin, &orig_stdout, 1);
	return (get_exit_status());
}

int	set_type_redi(t_tree *redi)
{
	t_redi_exec	*redi_exec;

	redi_exec = (t_redi_exec *)redi;
	if (redi_exec)
	{
		if (redi->type == INPUT_REDIRECTION)
			return (handle_redir_input((t_redi_exec *)redi));
		else if (redi->type == OUTPUT_REDIRECTION)
			return (handle_redir_output((t_redi_exec *)redi));
		else if (redi->type == APPEND_REDIRECTION)
			return (handle_redir_output((t_redi_exec *)redi));
		else if (redi->type == HEREDOC)
			return (handle_redir_input((t_redi_exec *)redi));
	}
	return (EXIT_SUCCESS);
}

int	handle_redir_input(t_redi_exec *redi)
{
	int		fd;
	char	**file_name;

	file_name = ft_split(redi->file_name, '\0');
	file_name = expand(file_name, 0);
	if (!redi)
		return (EXIT_SUCCESS);
	if (set_type_redi((t_tree *)redi->exec_child) != 0)
		return (set_exit_status(1), get_exit_status());
	if (redi->type == HEREDOC)
		fd = open(file_name[0], O_RDONLY);
	else
		fd = open(file_name[0], redi->flags, 0644);
	if (fd == -1)
	{
		perror(file_name[0]);
		return (set_exit_status(1), get_exit_status());
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (set_exit_status(0), get_exit_status());
}

int	handle_redir_output(t_redi_exec *redi)
{
	int		fd;
	char	**file_name;

	file_name = ft_split(redi->file_name, '\0');
	file_name = expand(file_name, 0);
	if (!redi)
		return (EXIT_SUCCESS);
	if (set_type_redi((t_tree *)redi->exec_child) != 0)
	{
		return (set_exit_status(1), get_exit_status());
	}
	fd = open(file_name[0], redi->flags, 0644);
	if (fd == -1)
	{
		perror(file_name[0]);
		return (set_exit_status(1), get_exit_status());
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (set_exit_status(0), get_exit_status());
}
