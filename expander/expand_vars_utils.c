#include "../include/minishell.h"

int	ft_isalnum_question(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '?')
		return (1);
	else
		return (0);
}

int	var_len(char *var)
{
	int	len;

	len = 0;
	while (var[len] && ft_isalnum_question(var[len]))
		len++;
	return (len);
}

void	identify_quotes(char c, int *quotes_found)
{
	if ((*quotes_found == 1 && c == '\'') || \
		(*quotes_found == 2 && c == '\"'))
		*quotes_found = 0;
	else if (!(*quotes_found) && (c == '\'' || c == '\"'))
	{
		if (c == '\'')
			*quotes_found = 1;
		else
			*quotes_found = 2;
	}
}

void	expand_add_to_buff(char *args_i, char **buff, int *j)
{
	int		len;
	char	*var_name;
	char	*var_value;
	t_env	*env;
	char	*tmp_buff;

	len = var_len(args_i + *j + 1);
	var_name = ft_substr(args_i, *j + 1, len);
	env = find_env_var(global.env, var_name);
	if (env)
		var_value = env->value;
	else
		var_value = handle_questionmark(var_name);
	tmp_buff = safe_malloc(sizeof(char) * (ft_strlen(var_value) + 1));
	ft_strlcpy(tmp_buff, var_value, ft_strlen(var_value) + 1);
	*j += len;
	if (!(*buff))
		*buff = tmp_buff;
	else
		*buff = ft_strjoin(*buff, tmp_buff);
}

void	add_char_to_buff(char **buff, char c)
{
	char	*single_char;

	single_char = safe_malloc(2);
	single_char[0] = c;
	single_char[1] = '\0';
	if (!(*buff))
		*buff = single_char;
	else
		*buff = ft_strjoin(*buff, single_char);
}
