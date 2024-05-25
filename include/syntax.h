#ifndef SYNTAX_H
# define SYNTAX_H

#include "tokenizer.h"

int	analyze(t_token *line);
void	check_andorpipe(t_token *node);
void	check_opening_parentheses(t_token *node);
void	check_closing_parentheses(t_token *node);
void check_redirection(t_token *node);





#endif