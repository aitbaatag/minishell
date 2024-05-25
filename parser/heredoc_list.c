#include "../include/parser.h"
#include <stdio.h>

// int count_heredocs(t_token *tokens)
// {
//     int count;

//     count = 0;
//     t_token *current;

//     current == tokens;
//     while (current)
//     {
//         if (current->type == HEREDOC)
//         {
//             count++;
//         }
//         current = current->next;
//     }
//     return count;
// }
void read_from_user(char *delimiter, t_redi_exec *node_heredoc, int i)
{
    char *line;
    char *path_tmp_file;

    path_tmp_file = ft_strjoin("here_doc", ft_itoa(i));
    node_heredoc->infile = open(path_tmp_file, O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, 0666);
    if (node_heredoc->infile == -1)
    {
        perror("open");
        return;
    }
    while (1)
    {
        line = readline("> ");
        if (!line)  
            break;
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(node_heredoc->infile, line, ft_strlen(line));
        write(node_heredoc->infile, "\n", 1);
        free(line);
    }
    close (node_heredoc->infile);
    // node_heredoc->infile = open(path_tmp_file, O_RDONLY);
    // free (path_tmp_file);
}
t_tree *creat_list_heredoc(t_token *tokens)
{
    t_token *ptr_token;
    t_redi_exec *list_heredoc;
    t_redi_exec *last_node;
    t_redi_exec *new_node;
    int i;
    char *delimiter;

    i = 0;
    list_heredoc = NULL;
    ptr_token = tokens;
    while (ptr_token)
    {
        if (ptr_token->type == HEREDOC)
        {
            delimiter = remove_quotes(ptr_token->next->value);
            new_node = new_node_here_doc(HEREDOC);
            read_from_user(delimiter, new_node, i);
            free (delimiter);
            if (!list_heredoc)
                list_heredoc = new_node;
            else
            {
                last_node->next = new_node;
                new_node->prev = last_node;
            }
            last_node = new_node;
            // Skip the delimiter token
            // ptr_token = ptr_token->next->next;
        }
        else if (ptr_token->type != HEREDOC && ptr_token->type != WORD)
        {
            new_node = new_node_here_doc(SPLIT);
            if (!list_heredoc)
                list_heredoc = new_node;
            else
            {
                last_node->next = new_node;
                new_node->prev = last_node;
            }
            last_node = new_node;
                        i++;
        }
            ptr_token = ptr_token->next;
    }
    return ((t_tree *)list_heredoc);
}
