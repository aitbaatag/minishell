#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"
typedef struct s_tree{
	token type;
}	t_tree;

typedef struct s_pipecmd {
	token	type;
	t_tree	*left;
	t_tree	*right;
}	t_pipe; 

typedef struct s_exec {
	token	type;
	char	*line;
	char	**args;
	t_tree	*child_redi;
	struct s_env	*env;
}	t_exec;

typedef struct s_logiccmd {
	token	type;
	t_tree	*left;
	t_tree	*right;
}	t_logic;

typedef struct s_redcmd {
	token	type;
	int		infile;
	int		outfile;
	char	*file_name;
	char	*dlmt;
	int		flags;
	t_tree	*exec_child;
	struct s_redcmd *next;
	struct s_redcmd *prev;
}	t_redi_exec;

typedef struct s_grouped_commands {
	token type;
	t_tree *child;
	t_tree *outer_redir;
} t_grp_exec;

//Tree Building Functions
t_tree *build_tree(t_token **tokens);
t_tree *link_root_tree(t_token **tokens, t_tree *right, t_redi_exec **list_heredoc);
t_tree *pipe_tree(t_token **tokens, t_redi_exec **list_heredoc);
t_tree *handling_redi(t_token **tokens, t_redi_exec **list_heredoc);
t_redi_exec	*handle_redirection(t_token **tokens, t_redi_exec **list_heredoc);
t_tree *add_node_tree(t_tree *left, t_tree *right);
t_tree *grouoped_cmd_tree(t_token **tokens, t_tree *redi_list, t_redi_exec **list_heredoc);

//Node Creation Functions
t_pipe *new_pipe();
t_exec* new_exec(int size_of_args);
t_grp_exec *new_grp_exec();
t_logic *new_logic(token type);
t_tree *node_logic(token type, t_tree *right, t_tree *left);
t_redi_exec *new_redi(t_token **tokens);

//Token Processing Functions
t_exec* get_exec_and_update_tokens(t_token **tokens);
char *init_arg(char *value);
void reverse_list_tokens(t_token **token);
void clean_list_tokens(t_token **tokens);
int size_of_args(t_token *token);
int visit_tokens(t_token **tokens);
t_redi_exec *get_node_heredoc(t_redi_exec **list_heredoc);
int	process_token(t_token **tokens, t_exec *exec_cmd, int *size);

// Heredoc Creation Functions
t_redi_exec *creat_list_heredoc(t_token *tokens);
t_redi_exec *new_node_here_doc(token type);
int check_expand(char *delimiter);

// String Manipulation Functions
char *get_substring(char *str, int *i, char delimiter);
char *append_substring(char *joined, char *str, int *i, char delimiter);
char *remove_quotes(char *str);

// Token Processing Functions
void reverse_list_tokens(t_token **token);
void clean_list_tokens(t_token **tokens);
void	read_from_user(char *delimiter, t_redi_exec *node_heredoc, int i, int flag);

#endif