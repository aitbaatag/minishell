#include "../include/parser.h"
t_tree *build_tree(t_token **tokens)
{
    t_redi_exec *list_heredoc;
    t_tree *tree;
    t_tree *right;

    right = NULL;
    clean_list_tokens(tokens); // remove space
    list_heredoc = creat_list_heredoc(*tokens);
    reverse_list_tokens(tokens); // move pointer to last node
    right = pipe_tree(tokens, &list_heredoc);
    tree = link_root_tree(tokens, right, &list_heredoc);
    return (tree);
}