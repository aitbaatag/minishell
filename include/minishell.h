#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "tokenizer.h"
#include "parser.h"
#include "envs.h"
#include "builtins.h"
typedef struct s_tree t_tree;
typedef struct s_data {
    char *line;
    t_token *tokens;
    t_tree *root;
} t_data;
#endif // MINISHELL_H