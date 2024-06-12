/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:46:29 by asadiqui          #+#    #+#             */
/*   Updated: 2024/06/12 19:17:41 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_exec	t_exec;

int		(*is_builtin(char *cmd))(t_exec *exec);
int		compare_env(const char *a, const char *b);
void	bubble_sort_env(char **env_array, size_t size);
void	print_sorted_env(t_env *envs);
int		add_var_to_envs_or_app_modif_exis(char *arg);
int		create_key_value_pair(char *arg, char **key, char **value);
void	update_existing_var(t_env *current, char *arg, char *value);
void	add_or_update_var(char *arg, char *key, char *value);
int		export_env_var(t_exec *exec);
int		builtin_env(t_exec *exec);
int		builtin_unset(char *key);
int		ft_unset(t_exec *exec);
int		ft_cd(t_exec *exec);
int		ft_pwd(t_exec *exec);
int		ft_echo(t_exec *exec);
int		ft_exit(t_exec *exec);

#endif