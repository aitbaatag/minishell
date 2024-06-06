#ifndef TOKENIZER_H
# define TOKENIZER_H

#include "minishell.h"

typedef struct s_redcmd t_redi_exec;
typedef enum e_token {
    WORD = 1 << 0,
    PIPE = 1 << 1,
    INPUT_REDIRECTION = 1 << 2,
    OUTPUT_REDIRECTION = 1 << 3,
    APPEND_REDIRECTION = 1 << 4,
    HEREDOC = 1 << 5,
    AND = 1 << 6,
    OR = 1 << 7,
    OPENING_PARENTHESES = 1 << 8,
    CLOSING_PARENTHESES = 1 << 9,
	WHITE_SPACE = 1 << 10,
	SUBSHELL = 1 << 11,
    EXEC = 1 << 12,
	REDIRECTION = INPUT_REDIRECTION | OUTPUT_REDIRECTION | APPEND_REDIRECTION | HEREDOC,
	LOGICAL = AND | OR,
	PARN = OPENING_PARENTHESES | CLOSING_PARENTHESES
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
int count_qoutes(char *str, char c);
int check_wildcard(char *str);
int    is_match(const char *f, const char *p);
void add_meant_file(t_token **tokens, char *namefile);
void listfile(char *expand, t_token **tokens);

#endif