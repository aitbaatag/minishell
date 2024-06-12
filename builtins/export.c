/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:57:31 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:12:32 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	bubble_sort_env(char **env_array, size_t size)
{
	size_t	i;
	size_t	j;
	char	*temp;
	int		swapped;

	i = -1;
	while (++i < size - 1)
	{
		j = 0;
		swapped = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp((const char *)env_array[j], (const char *)env_array[j
					+ 1]) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
	}
}

void	print_sorted_env(t_env *envs)
{
	char	**env_array;
	size_t	size;
	size_t	i;
	size_t	j;

	i = -1;
	env_array = env_to_array(envs);
	size = get_envp_size(NULL, envs, 1);
	bubble_sort_env(env_array, size - 1);
	while (++i < size)
	{
		j = 0;
		printf("declare -x ");
		while (env_array[i][j] != '=')
			printf("%c", env_array[i][j++]);
		if (env_array[i][j] == '=')
		{
			printf("=\"");
			while (env_array[i][++j])
				printf("%c", env_array[i][j]);
			printf("\"\n");
		}
		else
			printf("\n");
	}
}

int	add_var_to_envs_or_app_modif_exis(char *arg)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (create_key_value_pair(arg, &key, &value) != 0)
		return (1);
	add_or_update_var(arg, key, value);
	return (0);
}

int	export_env_var(t_exec *exec)
{
	int		i;
	t_env	*envs;

	envs = global.env;
	i = 1;
	i = 1;
	if (exec->args[1] == NULL)
	{
		print_sorted_env(envs);
	}
	else
	{
		while (exec->args[i])
		{
			if (add_var_to_envs_or_app_modif_exis(exec->args[i]) != 0)
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(exec->args[i], 2);
				ft_putstr_fd("'\033[0;31m: not a valid identifier\n\033[0m", 2);
				return (set_exit_status(1), get_exit_status());
			}
			i++;
		}
	}
	return (set_exit_status(0), get_exit_status());
}
