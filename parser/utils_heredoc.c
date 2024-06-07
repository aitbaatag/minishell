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
	int		start;
	int		length;

	start = *i;
	length = 0;
	if (delimiter != '\0')
	{
		start++; // Skip the opening quote
		(*i)++;
		while (str[*i] && str[*i] != delimiter)
		{
			(*i)++;
			length++;
		}
		(*i)++; // Move past the closing quote
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
	{
		new_joined = ft_strjoin(joined, substring);
		free(substring);
		free(joined);
	}
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
	// free(str);
	return (joined);
}
