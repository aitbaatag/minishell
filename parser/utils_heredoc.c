#include "../include/minishell.h"
t_redi_exec *new_node_here_doc(token type)
{
    t_redi_exec *redi;

    redi = safe_malloc(sizeof(t_redi_exec));
    redi->type = type;
    redi->fd = 0;
    redi->flags = O_RDONLY;
    redi->exec_child = NULL;
    redi->next = NULL;
    redi->prev = NULL;
    return (redi);
}

// char	*set_filename(t_redir *node, char *s, t_etype type)
// {
// 	char	*filename;
// 	bool	expand;

// 	if (type != HEREDOC)
// 		return (node->file = s, s);
// 	expand = true;
// 	filename = read_heardoc(s, &expand);
// 	node->expand = expand;
// 	if (!filename)
// 		return (NULL);
// 	return (node->file = filename, node->file);
// }
char *get_substring(char *str, int *i, char delimiter)
{
    char *result;
    int start = *i;
    int length = 0;

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

    result = ft_substr(str, start, length);
    return result;
}

char *append_substring(char *joined, char *str, int *i, char delimiter)
{
    char *substring;
    char *new_joined;

    substring = get_substring(str, i, delimiter);

    if (joined)
    {
        new_joined = ft_strjoin(joined, substring);
        free(substring);
        free(joined);
    }
    else
    {
        new_joined = substring;
    }

    return new_joined;
}

char *remove_quotes(char *str)
{
    char *joined = NULL;
    int i = 0;
    char *str1;
    char *str2;

    str1 = NULL;
    str2 = NULL;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            joined = append_substring(joined, str, &i, str[i]);
        }
        else
        {
            joined = append_substring(joined, str, &i, '\0');
        }
    }

    // free(str);
    return joined;
}
