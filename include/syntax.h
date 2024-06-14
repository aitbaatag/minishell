/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:47:02 by asadiqui          #+#    #+#             */
/*   Updated: 2024/06/14 01:36:04 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "minishell.h"

/*###################################
#			SYNTAX ANALYSIS			#
###################################*/
bool	analyze_syntax(t_token *tokens);
bool	select_check(t_token *tokens, bool *status);
bool	ambiguous_redirect(t_token *tokens);

/*###################################
#		CHECK	TOKEN	TYPES		#
###################################*/
void	print_syntax_error(t_token *node);
bool	check_andorpipe(t_token *node);
bool	check_parentheses(t_token *node);
bool	check_redirection(t_token *node);

/*###################################
#			OTHER	CHECK			#
###################################*/
bool	check_parn_nbr(t_token *node);
bool	check_closed_quotes(char *node);
bool	check_series_of_redirection_after_parn(t_token *node);

#endif