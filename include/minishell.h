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
#include "../libft/libft.h"
#include "tokenizer.h"
#include "parser.h"
#include "envs.h"
#include "builtins.h"
#include "executer.h"
#include "syntax.h"

typedef struct s_tree t_tree;
struct s_token;
typedef struct s_env t_env;

typedef	struct s_global {
    t_env   *env;
    int		status;
    int flag;
    int old_stdin;
    int old_stdout;
	char	*homedir;
}	t_global;

extern t_global global;

typedef struct s_data {
    char *line;
    t_token *tokens;
    t_tree *tree;
} t_data;

void	welcome(void);
void	sigint_handler(int signum);
void	eof_handler(void);

#endif