/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:08:54 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/14 09:10:53 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	*heredoc_signaled(void)
{
	static int	fd = -1;

	return (&fd);
}

void	heredoc_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	*heredoc_signaled() = dup(0);
	close(0);
	set_exit_status(130);
}

void	heredoc_eof(void)
{
	ft_putstr_fd(RED"minishell: warning: here-document \
		delimited by end-of-file\n"CLOSE, 2);
	set_exit_status(EXIT_SUCCESS);
}

void	ft_signaled(void)
{
	if (*heredoc_signaled() != -1)
	{
		dup2(*heredoc_signaled(), 0);
		close(*heredoc_signaled());
	}
}
