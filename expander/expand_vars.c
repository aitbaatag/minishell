/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:13 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/13 23:11:22 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expand_core1(char **buff, char *args_i, int *j, int *quotes)
{
	if (args_i[*j] == '$' && args_i[*j + 1] && args_i[*j + 1] != '\''
		&& args_i[*j + 1] != '\"')
		expand_add_to_buff(args_i, buff, j);
	else if (args_i[*j] == '$' && !(*quotes) && args_i[*j + 1] && (args_i[*j
				+ 1] == '\'' || args_i[*j + 1] == '\"'))
		(*j)++;
	else
		add_char_to_buff(buff, args_i[*j]);
	(*j)++;
}

static void	expand_core(char **buff, char *args_i, int *j, int *quotes)
{
	if (args_i[*j] == '$' && !(*quotes == 1) && args_i[*j + 1] \
		&& args_i[*j + 1] != '\'' && args_i[*j + 1] != '\"')
		expand_add_to_buff(args_i, buff, j);
	else if (args_i[*j] == '$' && !(*quotes) && args_i[*j + 1] \
		&& (args_i[*j + 1] == '\'' || args_i[*j + 1] == '\"'))
		(*j)++;
	else
		add_char_to_buff(buff, args_i[*j]);
	(*j)++;
}

char    **expand(char **args, int heredoc)
{
    char	*buff;
    int		quotes_found;
    int		i;
    int		j;
    int		k;
    int		tmp_index;

	char **tmp_args = safe_malloc(sizeof(char *) * 100);
	i = -1;
	while (args[++i])
		tmp_args[i] = ft_strdup(args[i]);
	tmp_index = 0;
	i = 0;
	while (args[i])
	{
		j = 0;
		buff = NULL;
		quotes_found = 0;
		while (args[i][j])
		{
			identify_quotes(args[i][j], &quotes_found);
			if (!heredoc)
				expand_core(&buff, args[i], &j, &quotes_found);
			else
				expand_core1(&buff, args[i], &j, &quotes_found);
		}
		if (!heredoc)
		{
			if (g_global.to_split)
			{
				k = 0;
				char **buff_to_array = ft_split(remove_quotes(buff), ' ');
				while (buff_to_array[k])
					tmp_args[tmp_index++] = buff_to_array[k++];
			}
			else
				tmp_args[tmp_index] = remove_quotes(buff);
		}
		else
			args[i] = buff;
		i++;
		if (!g_global.to_split)
			tmp_index++;
		g_global.to_split = 0;
	}
	if (!heredoc)
	{
		tmp_args[tmp_index] = NULL;
		args = tmp_args;
	}
	return (args);
}
