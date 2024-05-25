#include "../include/parser.h"
void reverse_list_tokens(t_token **token)
{
    if (!token || !(*token))
    {
        return;
    }
    while ((*token)->next)
        (*token) = (*token)->next;
}
int size_of_args(t_token *token)
{
    t_token *ptr;
    int size;

    size = 0;
    ptr = token;
    while (ptr)
    {
        if ((ptr->prev == NULL && ptr->type == WORD)
            || (ptr->type == WORD && ptr->prev
            && ptr->prev->type != INPUT_REDIRECTION &&
            ptr->prev->type != OUTPUT_REDIRECTION
            && ptr->prev->type != APPEND_REDIRECTION && ptr->prev->type != PARN &&  ptr->prev->type != HEREDOC))
            size++;
        else if (ptr->type == AND || ptr->type == OR || ptr->type == PIPE || ptr->type == CLOSING_PARENTHESES)
            return (size);
        else if (ptr->prev == NULL && ptr->type == WORD)
            size++;
        ptr = ptr->prev;
    }
    return (size);
}