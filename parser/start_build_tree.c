#include "../include/parser.h"
t_tree *build_tree(t_token **tokens)
{
    t_tree *tree;
    t_tree *right;

    right = NULL;
    (*tokens)->list_here_doc = creat_list_heredoc(*tokens);
    clean_list_tokens(tokens); // remove space
    reverse_list_tokens(tokens); // move pointer to last node
    right = pipe_tree(tokens);
    tree = link_root_tree(tokens, right);
    return (tree);
}