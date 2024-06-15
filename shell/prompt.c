/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 06:39:55 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/14 21:12:13 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_current_directory_prompt(char *cwd)
{
	int	b;
	int	i;

	b = 0;
	i = 0;
	while (cwd[i] && b < 3)
	{
		if (cwd[i] == '/')
			b++;
		i++;
	}
	return (ft_strdup(&cwd[i]));
}

char	*construct_prompt(t_env *env_user, char *path)
{
	char	*tmp_prompt;
	char	*prompt;

	if (!env_user || !env_user->value)
		prompt = ft_strdup(RED"known_user@minishell:~"CLOSE);
	else
	{
		prompt = ft_strjoin(env_user->value, "@minishell:~");
		prompt = ft_strjoin(ORANGE, prompt);
		prompt = ft_strjoin(prompt, CLOSE);
	}
	tmp_prompt = ft_strnstr(path, "/", ft_strlen(path));
	if (!tmp_prompt)
		prompt = ft_strjoin(prompt, RED"$ > "CLOSE);
	else
	{
		prompt = ft_strjoin(prompt, tmp_prompt);
		prompt = ft_strjoin(prompt, RED"$ > "CLOSE);
	}
	return (prompt);
}

char	*get_prompt(void)
{
	char	cwd[1024];
	t_env	*env_user;
	char	*prompt;

	prompt = NULL;
	env_user = find_env_var(g_global.env, "USER");
	getcwd(cwd, sizeof(cwd));
	if (env_user && env_user->value)
	{
		prompt = ft_strnstr(cwd, env_user->value, ft_strlen(cwd));
		if (!prompt)
			prompt = ft_strdup(env_user->value);
	}
	else
		prompt = get_current_directory_prompt(cwd);
	prompt = construct_prompt(env_user, prompt);
	return (prompt);
}
