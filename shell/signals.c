#include "../include/minishell.h"

void	sigint_handler_nonl(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler(int signum)
{
	(void)signum;
	printf("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_status(130);
}

void	eof_handler(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}