#ifndef BUILTINS_H
#define BUILTINS_H
#include "minishell.h"

//Export Functions
int compare_env(const char *a, const char *b);
void bubble_sort_env(char **env_array, size_t size);
void print_sorted_env(t_env *envs);
void add_var_to_envs_or_app_modif_exis(char *arg);
void export_env_var(char **args);
int    builtin_env();
int builtin_unset(char *key);
#endif