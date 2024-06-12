/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:12:33 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 17:37:51 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	cd_special_cases(t_exec *exec)
{
	t_env	*home;

	set_exit_status(1);
	if (!exec->args[1] || !ft_strcmp(exec->args[1], "~"))
	{
		home = find_env_var(global.env, "HOME");
		if (home)
			chdir(home->value);
		else
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (get_exit_status());
		}
	}
	else if (exec->args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (get_exit_status());
	}
	else if (exec->args[1] && chdir(exec->args[1]) == -1)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		return (get_exit_status());
	}
	return (0);
}

int	ft_cd(t_exec *exec)
{
	char	*oldpwd;
	char	newpwd[1024];

	oldpwd = ((find_env_var(global.env, "PWD"))->value);
	if (cd_special_cases(exec))
		return (get_exit_status());
	add_var_to_envs_or_app_modif_exis(ft_strjoin("OLDPWD=", oldpwd));
	getcwd(newpwd, sizeof(newpwd));
	add_var_to_envs_or_app_modif_exis(ft_strjoin("PWD=", newpwd));
	return (set_exit_status(0), get_exit_status());
}
