/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:57:55 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 22:25:39 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**env_to_array(t_env *envs)
{
	t_env	*ptr_envs;
	char	**env_array;
	int		i;
	size_t	size;

	size = get_envp_size(NULL, envs, 1);
	i = 0;
	env_array = safe_malloc((size + 1) * sizeof(char *));
	env_array[size] = NULL;
	ptr_envs = envs;
	while (ptr_envs)
	{
		env_array[i] = ft_strjoin(ptr_envs->key, "=");
		if (ptr_envs->value)
			env_array[i] = ft_strjoin(env_array[i], ptr_envs->value);
		ptr_envs = ptr_envs->next;
		i++;
	}
	return (env_array);
}

void	set_env(char **envp)
{
	int		i;
	char	pwd[1024];

	i = 0;
	if (!envp || !*envp)
	{
		getcwd(pwd, sizeof(pwd));
		add_or_modify_env_var(ft_strjoin("PWD=", pwd));
		add_envp("SHLVL=1");
		add_envp("_=/usr/bin/env");
	}
	while (envp[i])
	{
		add_envp(envp[i]);
		i++;
	}
}
