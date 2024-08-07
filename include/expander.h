/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:46:43 by asadiqui          #+#    #+#             */
/*   Updated: 2024/06/14 01:10:06 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/*##############################*|
/#			WILDCARDS			*|
|###############################*/

int		check_wildcard(char *str);
int		is_match(const char *f, const char *p);
void	add_meant_file(t_token **tokens, char *namefile);
void	listfile(char *expand, t_token **tokens);

/*##############################*|
/#			VARIABLES			*|
|###############################*/

char	**expand(char **args, int heredoc);
void	add_char_to_buff(char **buff, char c);
void	expand_add_to_buff(char *args_i, char **buff, int *j);
void	identify_quotes(char c, int *quotes_found);
int		var_len(char *var);
int		ft_isalnum_question(int c);
char	*handle_questionmark(char *var_name);
void	expand_status(char *var_name, int *i, char **buff);

#endif