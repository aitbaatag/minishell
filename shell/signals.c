#include "../include/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_status(130);
}

void	sigint_handler_nl(int signum)
{
	(void)signum;
	write(1, "\n", STDOUT_FILENO);
	// set_exit_status(100);
}

void	sigint_handler_exit(int signum)
{
	(void)signum;
	exit(0);
	set_exit_status(100);
}

void	heredoc_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("heredoc_handler\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	// close infile; free;
	// dup(0);
	close(0);
	set_exit_status(130);
}

void	eof_handler(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

void	heredoc_eof(void)
{
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", 2);
	set_exit_status(0);
}