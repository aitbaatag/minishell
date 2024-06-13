/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:13 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/13 00:24:36 by kait-baa         ###   ########.fr       */
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

void	expand(char **args, int heredoc)
{
	char	*buff;
	int		quotes_found;
	int		i;
	int		j;

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
			args[i] = remove_quotes(buff);
		else
			args[i] = buff;
		i++;
	}
}
