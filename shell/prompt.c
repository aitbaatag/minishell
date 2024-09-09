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

char	*get_current_directory_prompt(char *cwd, char *user)
{
	if (cwd[0] == '/' && cwd[1] == '\0')
		return (ft_strdup("/"));
	return (ft_strnstr(cwd, user, ft_strlen(cwd)));
}

char	*construct_prompt(char *username, char *path)
{
	char	*tmp_prompt;

	username = ft_strjoin(ORANGE, ft_strjoin(username,":~"));
	username = ft_strjoin(username, CLOSE);
	tmp_prompt = ft_strnstr(path, "/", ft_strlen(path));
	username = ft_strjoin(username, tmp_prompt);
	username = ft_strjoin(username, RED"$ -_- > "CLOSE);
	return (username);
}

char	*get_prompt(void)
{
	char	cwd[1024];
	char hostname[256];
    char *username;
	char	*prompt;
	
	prompt = NULL;
	if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("gethostname");
    }
	username = getlogin();
    if (username == NULL) {
        perror("getlogin");
    }
	getcwd(cwd, sizeof(cwd));
	prompt = get_current_directory_prompt(cwd, username);
	username = ft_strjoin(username, ft_strjoin("@", hostname));
	prompt = construct_prompt(username, prompt);
	return (prompt);
}
