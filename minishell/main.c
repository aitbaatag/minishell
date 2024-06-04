#include "../include/minishell.h"
t_global	global; 

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
        case 10: return "OPENING_PARENTHESES";
        case 11: return "CLOSING_PARENTHESES";
        case 12: return "WHITE_SPACE";
        case 13: return "STAR";
        case 14: return "SUBSHELL";
        case 15: return "EXEC";
        default: return "UNKNOWN";
    }
}

int main() {
    char *line;
    t_token *tokens;

    int i;

    i = 0;
	line = readline("minishell> "); // link with -lreadkine

    tokens = tokenization(line);
 
    
while (1)
{
        while (tokens != NULL) {
            if (tokens && tokens->value)
            {
                // printf ("jj\n");
             printf("%s_%s=> \n",  tokens->value, token_type_to_string(tokens->type));
            }
            tokens = tokens->next;
        }
}
    return 0;
}

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
                printf("Arguments: \n");
                char **args = exec_node->args;
                while (*args) {
                    printf("  %s\n", *args);
                    args++;
                }
                current = exec_node->child_redi;
                if (current)
                    printf ("redi ==> \n");
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
// int main() {
//     t_data *data;
//     t_global global;

// 	// global = malloc(sizeof(t_global));
//     global.env = NULL;
//     global.status = 0;
//     data = safe_malloc(sizeof(data));

//     // set_env(envp);
//     char *line;
//     t_token *tokens;
//     t_tree *root;
//     while (1)
//     {
// 	line = readline("minishell> "); // link with -lreadkine

//     tokens = tokenization(line);
//     root = build_tree(&tokens);
//     print_tree (root);
//     }
//     return 0;
// }