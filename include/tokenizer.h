#ifndef TOKENIZER_H
# define TOKENIZER_H

#include <stdlib.h>
#include "minishell.h"
typedef struct s_redcmd t_redi_exec;
typedef enum e_token {
    WORD,
    PIPE,
    INPUT_REDIRECTION,
    OUTPUT_REDIRECTION,
    APPEND_REDIRECTION,
    HEREDOC,
    AND,
    OR,
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    VARIABLE,
    OPENING_PARENTHESES,
    CLOSING_PARENTHESES,
    WHITE_SPACE,
	STAR,
	GROUPED_CMDS, //Subshell 
    EXEC,
	LOGICAL = AND | OR,
	REDIERCTION = INPUT_REDIRECTION | OUTPUT_REDIRECTION | APPEND_REDIRECTION | HEREDOC,
	PARN = OPENING_PARENTHESES | CLOSING_PARENTHESES,
    SPLIT
}	token;

typedef struct s_token
{
	token			type;
	char			*value;
    int             count;
    int             index;
	struct s_token	*next;
	struct s_token	*prev; 
    t_redi_exec *list_here_doc;
}   t_token;

t_token*	tokenization(char *line);
int	is_special(char c, int i);
t_token* new_node(char *value, token type);
void add_node_back(t_token **list_token, t_token *new_token);
token return_type(char *str, int count);
char *return_specials(char *str, int conut);
void add_token(t_token **token, char *str, int count);
void init_struct(t_token *list_tokens);
void is_quotes(t_token **token, char *str, int *i);
int is_variable(t_token **token, char *str);
int check_quotes(char *str);

#endif