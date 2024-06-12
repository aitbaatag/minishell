/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:00:09 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:10:05 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_redi_exec	*new_node_here_doc(token type)
{
	t_redi_exec	*redi;

	redi = safe_malloc(sizeof(t_redi_exec));
	redi->type = type;
	redi->flags = O_RDONLY;
	redi->exec_child = NULL;
	redi->next = NULL;
	redi->prev = NULL;
	return (redi);
}

char	*get_substring(char *str, int *i, char delimiter)
{
	int	start;
	int	length;

	start = *i;
	length = 0;
	if (delimiter != '\0')
	{
		start++;
		(*i)++;
		while (str[*i] && str[*i] != delimiter)
		{
			(*i)++;
			length++;
		}
		(*i)++;
	}
	else
	{
		while (str[*i] && (str[*i] != '\'' && str[*i] != '\"'))
		{
			(*i)++;
			length++;
		}
	}
	return (ft_substr(str, start, length));
}

char	*append_substring(char *joined, char *str, int *i, char delimiter)
{
	char	*substring;
	char	*new_joined;

	substring = get_substring(str, i, delimiter);
	if (joined)
		new_joined = ft_strjoin(joined, substring);
	else
		new_joined = substring;
	return (new_joined);
}

char	*remove_quotes(char *str)
{
	char	*joined;
	int		i;

	joined = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			joined = append_substring(joined, str, &i, str[i]);
		else
			joined = append_substring(joined, str, &i, '\0');
	}
	return (joined);
}
