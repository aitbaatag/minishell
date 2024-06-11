#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <stdbool.h>
#include "libft.h"
#include "tokenizer.h"
#include "parser.h"
#include "envs.h"
#include "builtins.h"
#include "executer.h"
#include "expander.h"
#include "syntax.h"
#include "garbage.h"

#define GREEN '\033[1;32m'
#define CLOSE '\033[0m'


typedef	struct s_global {
    t_env   *env;
    int		status;
    int fd;
    int break_2;
    t_garbage *garbage_list;
}	t_global;

extern t_global global;

typedef struct s_data {
    char *line;
    t_token *tokens;
    t_tree *tree;
} t_data;

void	welcome(void);
void	sigint_handler(int signum);
void	sigint_handler_nl(int signum);
void	sigint_handler_exit(int signum);
void	heredoc_handler(int signum);
int     *heredoc_error(void);
void	eof_handler(void);
void	heredoc_eof(void);

#endif