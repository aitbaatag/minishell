#include "../include/minishell.h"

int	check_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
int	is_match(const char *f, const char *p)
{
	while (*f && *p)
	{
		if (*p == '*')
		{
			while (*(p + 1) == '*')
				p++;
			if (*(p + 1) == '\0')
				return (1);
			while (*f && *f != *(p + 1))
				f++;
			if (*f == '\0')
				return (0);
			p++;
		}
		else if (*f != *p)
			return (0);
		else
		{
			f++;
			p++;
		}
	}
	return (*f == '\0' && *p == '\0');
}
void	add_meant_file(t_token **tokens, char *namefile)
{
	t_token	*new_token;

	new_token = new_node(namefile, WORD);
	add_node_back(tokens, new_token);
}
void	listfile(char *expand, t_token **tokens)
{
	struct dirent *namelist;
	DIR *dir;
	int flag;

	flag = 0;
	dir = opendir(".");
	namelist = readdir(dir);
	while (namelist)
	{
		if (ft_strncmp(namelist->d_name, ".", 1) == 0)
		{
			namelist = readdir(dir);
			continue ;
		}
		if (is_match(namelist->d_name, expand))
		{
			add_meant_file(tokens, namelist->d_name);
			if (flag == 0)
				flag = 1;
		}
		namelist = readdir(dir);
	}
	if (flag == 0)
		add_meant_file(tokens, expand);
}