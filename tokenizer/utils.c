#include "../include/minishell.h"

int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '&' || c == '|' ||
		c == '\"' || c == '\'' || c == '(' || c == ')')
		return (1);
	return (0);
}
int	count_qoutes(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	is_quotes(t_token **token, char *str, int *i)
{
	t_token *new_token;
	int n;

	n = 0;
	n++;
	while (str[n])
	{
		if (str[n] == str[0])
			break ;
		n++;
	}
	*i += n;
	if (n == 1)
		return ;
	new_token = new_node(ft_substr(str, 0, n + 1), return_type(str, 0));
	if (!new_token)
		return ;
	add_node_back(token, new_token);
}

// char	other_quote(char quote)
// {
// 	if (quote == '\'')
// 		return ('\"');
// 	else
// 		return ('\'');
// }

// void	is_quotes(t_token **token, char *str, int *i)
// {
// 	t_token *new_token;
// 	int		n;
// 	int		even;

// 	n = 0;
// 	even = 0;
// 	while (str[n])
// 	{
// 		if (str[n] == str[0])
// 		{
// 			if ((str[n + 1] == ' ' || str[n + 1] == other_quote(str[0])) && even)
// 				break ;
// 			else
// 			{
// 				if (even)
// 					even = 0;
// 				else
// 					even = 1;
// 			}
// 		}
// 		n++;
// 	}
// 	*i += n;
// 	if (n == 1)
// 		return ;
// 	new_token = new_node(ft_substr(str, 0, n + 1), return_type(str, 0));
// 	if (!new_token)
// 		return ;
// 	add_node_back(token, new_token);
// }
