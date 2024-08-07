/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:57:39 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 22:30:47 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_append_var(int *flag, char *c)
{
	if (*c == '+' && *(c + 1) == '=')
	{
		*flag = 1;
		return (1);
	}
	return (0);
}

int	create_key_value_pair(char *arg, char **key, char **value)
{
	char	*delimiter;
	int		i;

	i = 1;
	delimiter = NULL;
	delimiter = ft_strchr(arg, '=');
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	while (arg[i])
	{
		if ((arg + i) == delimiter || (((arg + (i + 1)) == delimiter)
				&& arg[i] == '+'))
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	if (delimiter)
		*value = create_value(delimiter + 1);
	else
		*value = ft_strdup("");
	*key = create_key(arg, delimiter);
	return (0);
}

void	update_existing_var(t_env *current, char *arg, char *value)
{
	int		i;
	int		flag;
	char	*new_value;

	i = 0;
	flag = 0;
	new_value = NULL;
	while (arg[i])
	{
		if (check_append_var(&flag, &arg[i]))
			break ;
		i++;
	}
	if (flag == 1)
	{
		new_value = ft_strjoin(current->value, value);
		current->value = new_value;
	}
	else
		current->value = ft_strdup(value);
}

void	add_or_update_var(char *arg, char *key, char *value)
{
	t_env	*current;

	current = find_env_var(g_global.env, key);
	if (current)
	{
		update_existing_var(current, arg, value);
	}
	else
	{
		add_envp(arg);
	}
}
