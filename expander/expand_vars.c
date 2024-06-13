/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:13:13 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/13 07:11:38 by asadiqui         ###   ########.fr       */
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

// int	count_sub_args(char *arg)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] == ' ')
// 			count++;
// 		i++;
// 	}
// 	return (count + 1);
// }

char	**expand(char **args, int heredoc)
{
	char	*buff;
	// char	**new_args;
	char	**tmp_args;
	int		quotes_found;
	char **split_args;
	int		i;
	int		j;
	int n;
	int	size;
	int k;

	k = 0;
	size = 0;
	n = 0;
	// printf("expander start\n");
	i = 0;
	while (args[size])
		size++;
	tmp_args = safe_malloc(sizeof(char *) * size + 1);
	tmp_args[size] = NULL;
	while (args[n])
	{
		tmp_args[n] = ft_strdup(args[n]);
		n++;
	}
	while (tmp_args[i])
	{
		j = 0;
		buff = NULL;
		quotes_found = 0;
		while (args[i][j])
		{
			identify_quotes(tmp_args[i][j], &quotes_found);
			if (!heredoc)
				expand_core(&buff, tmp_args[i], &j, &quotes_found);
			else
				expand_core1(&buff, tmp_args[i], &j, &quotes_found);
		}
		if (!heredoc)
		{
			if (global.y)
			{
				global.y = 0;
				n = 0;
				split_args = ft_split(buff, ' ');
				while (split_args[n])
				{
					n++;
					size++;
				}
				n = 0;
				args = safe_malloc(sizeof(char *) * size);
				args[size] = NULL;
				n = 0;
				while (split_args[n])
				{
					args[k] = remove_quotes(split_args[n]);
					n++;
					k++;
				}
				printf ("%s => %d\n", args[k], k);
			}
			else
			{
				args[k] = remove_quotes(buff);
			printf ("%s ==> %d\n", args[k], k);
				k++;
			}
		}
		else
			args[k] = buff;
		i++;
		// args[k] = ft_strdup(tmp_args[k]);
	}
	// printf ("%s\n", args[1]);
	// if (!heredoc)
	// {
	// 	// int sub_args;
	// 	// int	total_subs = 0;
	// 	// i = 0;
	// 	// while (args[i])
	// 	// {
	// 	// 	sub_args = count_sub_args(args[i]);
	// 	// 	total_subs += sub_args;
	// 	// 	new_args = ft_split(args[i], ' ');
	// 		// j =0;
	// 		// while (new_args[j])
	// 		// printf("new_args_j: ;%s;", new_args[j++]);
	// 	// 	new_args += sub_args;
	// 	// 	i++;
	// 	// }
	// 	// printf("total subs: %d\n", total_subs);
	// 	// i = 0;
	// 	// while (new_args[i])
	// 	// 	printf("new_args_i: ;%s;\n", new_args[i++]);
	// 	// new_args -= (total_subs);
	// 	// i = 0;
	// 	// while (new_args[i])
	// 	// 	printf("new_args_i: ;%s;\n", new_args[i++]);
	// 	// printf("no segv\n");
	// 	// if (!new_args)
	// 	// 	{
	// 	// 		printf("no args\n");
	// 	// 	}
	// 	args = new_args;
	// }
	return (args);
}
