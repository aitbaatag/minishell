#ifndef SYNTAX_H
# define SYNTAX_H

#include "minishell.h"

bool	analyze_syntax(t_token *tokens);
bool	check_andorpipe(t_token *node);
bool	check_parn_nbr(t_token *node);
bool	check_parentheses(t_token *node);
bool	check_redirection(t_token *node);
bool	check_quotes1(char *node);

#endif