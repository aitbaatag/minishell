#include "../include/minishell.h"
token check_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return WHITE_SPACE;
	return WORD;
}
token check_special_characters(char *str, int count)
{
    if (count == 1) // Handle single character special tokens
    {
        if (!ft_strcmp(str, ">"))
            return OUTPUT_REDIRECTION;
        else if (!ft_strcmp(str, "<"))
            return INPUT_REDIRECTION;
        else if (!ft_strcmp(str, "|"))
            return PIPE;
        else if (!ft_strncmp(str, "(", 1))
            return OPENING_PARENTHESES;
        else if (!ft_strncmp(str, ")", 1))
            return CLOSING_PARENTHESES;
    }
    else if (count == 2) // Handle double character special tokens
    {
        if (!ft_strcmp(str, ">>"))
            return APPEND_REDIRECTION;
        else if (!ft_strcmp(str, "<<"))
            return HEREDOC;
        else if (!ft_strcmp(str, "&&"))
            return AND;
        else if (!ft_strcmp(str, "||"))
            return OR;
    }
    return WORD;
}

token return_type(char *str, int count)
{
	token result = check_whitespace(*str);
	if (result != WORD)
		return result;
	return check_special_characters(str, count);
}
