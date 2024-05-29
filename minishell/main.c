#include "../include/minishell.h"

char *token_type_to_string(int type) {
    switch (type) {
        case 0: return "WORD";
        case 1: return "PIPE";
        case 2: return "INPUT_REDIRECTION";
        case 3: return "OUTPUT_REDIRECTION";
        case 4: return "APPEND_REDIRECTION";
        case 5: return "HEREDOC";
        case 6: return "AND";
        case 7: return "OR";
        case 8: return "DOUBLE_QUOTE";
        case 9: return "SINGLE_QUOTE";
        case 10: return "VARIABLE";
        case 11: return "OPENING_PARENTHESES";
        case 12: return "CLOSING_PARENTHESES";
        case 13: return "WHITE_SPACE";
        case 14: return "STAR";
        case 15: return "SUBSHELL";
        case 16: return "EXEC";
        default: return "UNKNOWN";
    }
}

// int main() {
//     char *line;
//     t_token *tokens;
//     // t_redi_exec *list_heredoc;
//     // t_exec *ptr;
//     // t_redi_exec *ptr2;
//     int i;
//     // char *line2;

//     i = 0;
// 	line = readline("minishell> "); // link with -lreadkine
//     // add_history_time(line);

//     // tokenscopy = tokens;
//     tokens = tokenization(line);
//     // line = remove_quotes(tokens->next->next->value);
//     // printf ("%s\n", line);
//     clean_list_tokens(&tokens);
//     // list_heredoc = (t_redi_exec *)creat_list_heredoc(tokens);
//     // while (list_heredoc)
//     // {
//         // ptr2 = get_node_heredoc(&list_heredoc);
//         // printf ("%s\n", ptr2->file_name);
//         // ptr2 = get_node_heredoc(&list_heredoc);
//         // printf ("%s\n", ptr2->file_name);
//     //     list_heredoc = list_heredoc->next;
//     // }
// //     reverse_list_tokens(&tokens);

// //     ptr = get_exec_and_update_tokens(&tokens);
// //     while (ptr->args[i])
// //     {
// //         // printf ("jj");
// //         printf ("..%s..\n", ptr->args[i]);
// //         i++;
// //     }
    
    
// // //while (1)
// // //{
//         while (tokens != NULL) {
//             if (tokens && tokens->value)
//             {
//                 // printf ("jj\n");
//              printf("%s_%s=> \n",  tokens->value, token_type_to_string(tokens->type));
//             }
//             tokens = tokens->next;
//         }
// // // 	// analyze(tokenscopy);
// // // //}
//     return 0;
// }
// void print_tree(t_tree *root) {
//     if (root == NULL) {
//         printf("NULL\n");
//         return;
//     }

//     // Determine the type of the node based on its structure
//     if (root == NULL) {
//         printf("Empty node\n");
//         return;
//     }

//     // Print the appropriate information based on the type of node
//     if (root->type == PIPE) {
//         printf("PIPE\n");
//         printf("Left subtree:      ");
//         print_tree(((t_pipe *)root)->left);
//         printf("Right subtree:     ");
//         print_tree(((t_pipe *)root)->right);
//     } else if (root->type == EXEC) {
//         printf("EXEC\n");
//         t_exec *exec = (t_exec *)root;
//         printf("Path: %s\n", exec->path);
//         printf("Arguments: \n");
//         char **args = exec->args;
//         while (*args) {
//             printf("  %s\n", *args);
//             args++;
//         }
//         print_tree(((t_exec*)root)->child_redi);
//     } else if (root->type == AND || root->type == OR) {
//         if (root->type == AND)
//             printf("AND\n");
//         if (root->type == OR)
//             printf("OR\n");
//         printf("Left subtree:\n");
//         print_tree(((t_logic *)root)->left);
//         printf("Right subtree:\n");
//         print_tree(((t_logic *)root)->right);
//     } else if (root->type == SUBSHELL) {
//         printf("GROUPED_COMMANDS\n");
//         printf("Child subtree:\n");
//         print_tree(((t_grp_exec *)root)->child);
//     }
//     else if (root->type == APPEND_REDIRECTION) {
//         printf("append \n");
//         t_redi_exec *redcmd = (t_redi_exec*)root;
//         // printf("Mode: %s\n", redcmd->mode);
//         printf("Filename: %s\n", redcmd->file_name);
//         print_tree(redcmd->exec_child);
//     }
//     else if (root->type == INPUT_REDIRECTION) {
//         printf("input \n");
//         t_redi_exec *redcmd = (t_redi_exec*)root;
//         // printf("Mode: %s\n", redcmd->mode);
//         printf("Filename: %s\n", redcmd->file_name);
//         print_tree(redcmd->exec_child);
//     }
//     else if (root->type == OUTPUT_REDIRECTION) {
//         printf("output \n");
//         t_redi_exec *redcmd = (t_redi_exec*)root;
//         // printf("Mode: %s\n", redcmd->mode);
//         printf("Filename: %s\n", redcmd->file_name);
//         print_tree(redcmd->exec_child);
//     }
//     else {
//         printf("Unknown node type\n");
//     }
// }
void print_tree2(t_tree *root) {
    if (root == NULL) {
        printf("NULL\n");
        return;
    }

    t_tree *current = root;
    while (current != NULL) {
        switch (current->type) {
            case EXEC: {
                t_exec *exec_node = (t_exec *)current;
                printf("EXEC\n");
                printf("Path: %s\n", exec_node->path);
                printf("Arguments: \n");
                char **args = exec_node->args;
                while (*args) {
                    printf("  %s\n", *args);
                    args++;
                }
                current = exec_node->child_redi;
                if (current)
                    printf ("redi ==> ");
                break;
            }
            case APPEND_REDIRECTION:
            case INPUT_REDIRECTION:
            case OUTPUT_REDIRECTION:
            case HEREDOC: {
                t_redi_exec *redi_node = (t_redi_exec *)current;
                printf("%s\n", current->type == APPEND_REDIRECTION ? "APPEND_REDIRECTION" :
                                  current->type == INPUT_REDIRECTION ? "INPUT_REDIRECTION" :
                                  current->type == OUTPUT_REDIRECTION ? "OUTPUT_REDIRECTION" : "HEREDOC");
                printf("Filename: %s\n", redi_node->file_name);
                current = redi_node->exec_child;
                break;
            }
            default:
                printf("Unknown node type\n");
                current = NULL; // End loop for unknown node type
                break;
        }
    }
}
void print_tree(t_tree *root) {
    if (root == NULL) {
        printf("NULL\n");
        return;
    }

    t_tree *current = root;
    while (current != NULL) {
        switch (current->type) {
            case PIPE: {
                t_pipe *pipe_node = (t_pipe *)current;
                printf("PIPE\n");
                printf("Left subtree:      ");
                print_tree(pipe_node->left);
                printf("Right subtree:     ");
                print_tree(pipe_node->right);
                current = NULL; // End loop for PIPE node
                break;
            }
            case EXEC: {
                t_exec *exec_node = (t_exec *)current;
                printf("EXEC\n");
                printf("Path: %s\n", exec_node->path);
                printf("Arguments: \n");
                char **args = exec_node->args;
                while (*args) {
                    printf("  %s\n", *args);
                    args++;
                }
                current = exec_node->child_redi;
                if (current)
                    printf ("redi ==> ");
                break;
            }
            case AND:
            case OR: {
                t_logic *logic_node = (t_logic *)current;
                printf("%s\n", current->type == AND ? "AND" : "OR");
                printf("Left subtree:\n");
                print_tree(logic_node->left);
                printf("Right subtree:\n");
                print_tree(logic_node->right);
                current = NULL; // End loop for AND/OR node
                break;
            }
            case SUBSHELL: {
                t_grp_exec *grp_node = (t_grp_exec *)current;
                printf("GROUPED_COMMANDS\n");
                printf("Child subtree:\n");
                current = grp_node->child;
                if (grp_node->outer_redir)
                {
                    printf ("outer_redi\n");
                    print_tree2(grp_node->outer_redir);
                }
                break;
            }
            case APPEND_REDIRECTION:
            case INPUT_REDIRECTION:
            case OUTPUT_REDIRECTION:
            case HEREDOC: {
                t_redi_exec *redi_node = (t_redi_exec *)current;
                printf("%s\n", current->type == APPEND_REDIRECTION ? "APPEND_REDIRECTION" :
                                  current->type == INPUT_REDIRECTION ? "INPUT_REDIRECTION" :
                                  current->type == OUTPUT_REDIRECTION ? "OUTPUT_REDIRECTION" :
                                  current->type == HEREDOC ? "HEREDOC" : "UNKNOWN_TYPE");
                printf("Filename: %s\n", redi_node->file_name);
                printf("delimtr: %s\n", redi_node->dlmt);
                current = redi_node->exec_child;
                break;
            }
            default:
                printf("Unknown node type\n");
                current = NULL; // End loop for unknown node type
                break;
        }
    }
}
int main() {
    char *line;
    t_token *tokens;
    t_tree *root;

	line = readline("minishell> "); // link with -lreadkine

    tokens = tokenization(line);
    root = build_tree(&tokens);
    print_tree (root);
    return 0;
}