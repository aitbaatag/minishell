/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:08 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/13 00:05:59 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_status(char *var_name, int *i, char **buff)
{
	char	*tmp;
	int		len;

	tmp = ft_itoa(get_exit_status());
	len = ft_strlen(tmp);
	while (var_name[*i])
	{
		len++;
		(*i)++;
	}
	*buff = safe_malloc(sizeof(char) * (len + 1));
	ft_strlcpy(*buff, tmp, ft_strlen(tmp) + 1);
	ft_strlcpy(*buff + ft_strlen(tmp), var_name + 1, ft_strlen(var_name) + 1);
}

char	*handle_questionmark(char *var_name)
{
	char	*buff;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(var_name);
	if (var_name[i++] == '?')
		expand_status(var_name, &i, &buff);
	else
	{
		while (var_name[i] && var_name[i] != '?')
			i++;
		buff = safe_malloc(sizeof(char) * (len - i + 1));
		ft_strlcpy(buff, var_name + i, len - i + 1);
	}
	return (buff);
}
