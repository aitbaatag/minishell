#include "../include/parser.h"
t_tree *grouoped_cmd_tree(t_token **tokens, t_tree *redi_list)
{
    t_grp_exec *grp;
    t_tree *mini_tree; // right
    t_tree *redi_child;

    redi_child = NULL;
    grp = new_grp_exec();
    if (redi_child && redi_child->type == EXEC) // can delet 
        printf ("syntax error\n");

    if ((*tokens) && (*tokens)->type == CLOSING_PARENTHESES)
    {
        (*tokens) = (*tokens)->prev;
        mini_tree = pipe_tree(tokens);
    }
    if ((*tokens) && ((*tokens)->type == AND || (*tokens)->type == OR))
        mini_tree = link_root_tree(tokens, mini_tree);
    grp->child = mini_tree;
    grp->outer_redir = redi_list;
    if (!(*tokens) || (*tokens)->type == OPENING_PARENTHESES)
        (*tokens) = (*tokens)->prev;

    return ((t_tree *)grp);
}

t_tree *exec_tree(t_token **tokens)
{
    t_exec *exec;
    t_token *ptr;
    int args;

    if (!(*tokens))
        return (NULL);
    ptr = (*tokens);
    args = 0;
    while (ptr && (ptr->type == WORD))
    {
        ptr = ptr->prev;
        args++;
    }
    ptr = (*tokens);
    exec = new_exec(args);
    while ((*tokens) && ((*tokens)->type == WORD))
    {
        exec->args[args - 1 ] = init_arg((*tokens)->value);
        (*tokens) = (*tokens)->prev;
        args--;
    }
    return ((t_tree*)exec);
}
t_tree *link_root_tree(t_token **tokens, t_tree *right)
{
    t_tree *left;
    t_token *ptr;

    left = NULL;
    ptr = (*tokens);
    if (!(*tokens))
        return (right);
    if ((*tokens)->type == AND || (*tokens)->type == OR)
    {
        (*tokens) = (*tokens)->prev;
        left = pipe_tree(tokens);
        left = node_logic(ptr->type, link_root_tree(tokens, left), right);
        return (left);
    }
    if (!(*tokens) || (*tokens)->type == OPENING_PARENTHESES)
        return (right);
    return (left);
}
t_tree *handling_redi(t_token **tokens)
{
    t_redi_exec *redi_exec;
    t_exec *exec;

    redi_exec = NULL;
    if (!(*tokens))
        return (NULL);
    exec = get_exec_and_update_tokens(tokens); // remove cmd with flags / store it in varaible and return it if no cmd just return NULL;
    if ((*tokens) && (*tokens)->prev && (*tokens)->prev->type == HEREDOC)
    {
        redi_exec = get_node_heredoc((*tokens)->list_here_doc);
        (*tokens) = (*tokens)->prev->prev;
    }
    else if ((*tokens) && (*tokens)->prev && ((*tokens)->prev->type & REDIERCTION))
    {
        redi_exec = new_redi(tokens); // skip file name redi
        if ((*tokens)->prev->prev)
            (*tokens) = (*tokens)->prev->prev;
        else
            (*tokens) = NULL;
        redi_exec->exec_child = (t_tree*)handling_redi(tokens);
    }
    if (exec)
    {
        exec->child_redi = (t_tree*)redi_exec;
        return (t_tree*)exec;
    }
    return (t_tree*)redi_exec;
}
t_tree *pipe_tree(t_token **tokens)
{
    t_tree *tree_exec; // right

    if ((!*tokens))
        return (NULL);
    tree_exec = NULL;
    while ((*tokens))
    {
        if ((*tokens)->type == PIPE)
        {
            (*tokens) = (*tokens)->prev;
            tree_exec = add_node_tree(tree_exec, pipe_tree(tokens));
        }
        else if ((*tokens)->type == CLOSING_PARENTHESES)
            tree_exec = grouoped_cmd_tree(tokens, tree_exec);
        else if ((*tokens)->type == OPENING_PARENTHESES)
            return (tree_exec);
        else if ((*tokens)->type == OR || (*tokens)->type == AND)
            return (tree_exec);
        else if (visit_tokens(tokens))
            tree_exec = handling_redi(tokens);
        else
            tree_exec = exec_tree(tokens);
    }
    return (tree_exec);
}