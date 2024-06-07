#include "../include/minishell.h"

int	is_special(char c, int i)
{
	if (i == 0)
	{
		if (c == '<' || c == '>' || c == '&' || c == '|' ||
			c == '(' || c == ')')
			return (1);
	}
	else
	{
		if (c == '<' || c == '>' || c == '&' || c == '|' ||
			c == '\"' || c == '\'' || c == '(' || c == ')')
			return (1);
	}
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
	new_token = new_node(ft_substr(str, 0, n + 1), return_type(str, 0));
	if (!new_token)
		return ;
	add_node_back(token, new_token);
}