#include "../include/parser.h"
t_exec* get_exec_and_update_tokens(t_token **tokens)
{
    t_exec *exec_cmd;
    t_token *ptr;
    t_token *temp;
    int size;
    
    size = 0;
    ptr = (*tokens);
    size = size_of_args(ptr);
    exec_cmd = new_exec(size);
    while (ptr)
    {
        if ((ptr->prev == NULL && ptr->type == WORD) || (ptr->type == WORD && ptr->prev && !(ptr->prev->type & REDIERCTION)))
        {
            //store word and remove it
            exec_cmd->args[size - 1] = init_arg(ptr->value);
            temp = ptr;
            if (ptr->prev)
                ptr->prev->next = ptr->next;
            if (ptr->next)
                ptr->next->prev = ptr->prev;
            if (ptr == (*tokens))
                (*tokens) = ptr->prev;
            ptr = ptr->prev;
            size--;
            free(temp->value);
            free (temp);
        }
        else if (ptr->type == AND || ptr->type & LOGICAL || ptr->type & PARN ||  ptr->type == HEREDOC)
            return (exec_cmd);
        else
            ptr = ptr->prev;
    }
    return (exec_cmd);
}
// t_token *update_pointer(t_token *tokens)
// {
//     while (tokens)
//     {
//         if (tokens->type != WORD)
//             break;
//         tokens = tokens->prev;
//     }
//     return (tokens);
// }
t_redi_exec *get_node_heredoc(t_redi_exec *list_heredoc)
{
    t_redi_exec *ptr;

    reverse_list_tokens(&list_heredoc);
    ptr = list_heredoc;
    list_heredoc = list_heredoc->prev;
    return (ptr);
}
int visit_tokens(t_token **tokens)
{
    t_token *ptr;

    ptr = (*tokens);
    if (!ptr || !ptr->prev)
        return 0;
    while (ptr && ptr->prev && ptr->type != AND
        && ptr->type != OR && ptr->type != PIPE
        && ptr->type != CLOSING_PARENTHESES
        && ptr->type != OPENING_PARENTHESES)
    {
        if (ptr->type == WORD && (ptr->prev->type & REDIERCTION))
            return (1);
        ptr = ptr->prev;
    }
    return (0);
}
void clean_list_tokens(t_token **tokens) {
    t_token *ptr_tokens;
    t_token *temp;
    
    ptr_tokens = (*tokens);
    while (ptr_tokens)
    {
        if (ptr_tokens->type == WHITE_SPACE)
        {
            temp = ptr_tokens;
            if (ptr_tokens->prev)
                ptr_tokens->prev->next = ptr_tokens->next;
            if (ptr_tokens->next)
                ptr_tokens->next->prev = ptr_tokens->prev;
            if (ptr_tokens == (*tokens))
                *tokens = ptr_tokens->next;
            ptr_tokens = ptr_tokens->next;
            free(temp->value);
            free(temp);
        }
        else
            ptr_tokens = ptr_tokens->next;
    }
}