#ifndef ENVS_H
#define ENVS_H
#include "minishell.h"

typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
	struct s_env *prev;
} t_env;

void set_env(char **envp);
char **env_to_array(t_env *envs);
char **copy_envp(char **envp);
void add_env_node_to_list(t_env *new);
char *create_value(char *value_start);
char *create_key(char *env, char *delimiter);
t_env *create_env_node(char *env);
void add_envp(char *env);
size_t get_envp_size(char **envp, t_env *envs, int i);
t_env *find_env_var(t_env *envs, char *key);
#endif