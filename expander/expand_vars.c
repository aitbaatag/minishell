/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:13 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/14 12:07:33 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expand_inner_core_heredoc(\
	char **buff, char *args_i, int *j, int *quotes)
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

static void	expand_inner_core(char **buff, char *args_i, int *j, int *quotes)
{
	if (args_i[*j] == '$' && !(*quotes == 1) && args_i[*j + 1] \
		&& args_i[*j + 1] != '\'' && args_i[*j + 1] != '\"' && \
		!(args_i[*j + 1] == 32 || (7 <= args_i[*j + 1] \
		&& args_i[*j + 1] <= 13)) && args_i[*j + 1] != '/')
		expand_add_to_buff(args_i, buff, j);
	else if (args_i[*j] == '$' && !(*quotes) && args_i[*j + 1] \
		&& (args_i[*j + 1] == '\'' || args_i[*j + 1] == '\"'))
		(*j)++;
	else
		add_char_to_buff(buff, args_i[*j]);
	(*j)++;
}

static void	split_arg_by_space(char *buff, char ***tmp_args, int *tmp_index)
{
	char	**buff_to_array;
	int		k;

	if (g_global.to_split)
	{
		k = 0;
		buff_to_array = ft_split(remove_quotes(buff), ' ');
		while (buff_to_array[k])
			(*tmp_args)[(*tmp_index)++] = buff_to_array[k++];
	}
	else
		(*tmp_args)[(*tmp_index)] = remove_quotes(buff);
}

static void	expand_core(\
	char **args_i, int heredoc, char ***tmp_args, int *tmp_index)
{
	char	*buff;
	int		j;
	int		quotes_found;

	buff = NULL;
	j = 0;
	quotes_found = 0;
	while ((*args_i)[j])
	{
		identify_quotes((*args_i)[j], &quotes_found);
		if (!heredoc)
			expand_inner_core(&buff, *args_i, &j, &quotes_found);
		else
			expand_inner_core_heredoc(&buff, *args_i, &j, &quotes_found);
	}
	if (!heredoc)
		split_arg_by_space(buff, tmp_args, tmp_index);
	else
		*args_i = buff;
	if (!g_global.to_split)
		(*tmp_index)++;
	g_global.to_split = 0;
}

char	**expand(char **args, int heredoc)
{
	char	**tmp_args;
	int		i;
	int		tmp_index;

	tmp_args = safe_malloc(sizeof(char *) * 100);
	i = -1;
	while (args[++i])
		tmp_args[i] = ft_strdup(args[i]);
	tmp_index = 0;
	i = 0;
	while (args[i])
	{
		expand_core(&args[i], heredoc, &tmp_args, &tmp_index);
		i++;
	}
	if (!heredoc)
	{
		tmp_args[tmp_index] = NULL;
		args = tmp_args;
	}
	return (args);
}
