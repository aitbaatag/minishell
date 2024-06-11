#include "../include/minishell.h"

int	check(int *flag, char *c)
{
	if (*c == '+' && *(c + 1) == '=')
	{
		*flag = 1;
		return (1);
	}
	return (0);
}
int	create_key_value_pair(char *arg, char **key, char **value)
{
	char	*delimiter;
	int		i;

	i = 1;
	delimiter = NULL;
	delimiter = ft_strchr(arg, '=');
	if (!ft_isalpha(arg[0]))
		return (1);
	while (arg[i])
	{
		if ((arg + i) == delimiter || (((arg + (i + 1)) == delimiter)
				&& arg[i] == '+'))
			break ;
		if (!ft_isalnum(arg[i]))
			return (1);
		i++;
	}
	if (delimiter)
		*value = create_value(delimiter + 1);
	else
		*value = ft_strdup("");
	*key = create_key(arg, delimiter);
	return (0);
}

void	update_existing_var(t_env *current, char *arg, char *value)
{
	int		i;
	int		flag;
	char	*new_value;

	i = 0;
	flag = 0;
	new_value = NULL;
	while (arg[i])
	{
		if (check(&flag, &arg[i]))
			break ;
		i++;
	}
	if (flag == 1)
	{
		new_value = ft_strjoin(current->value, value);
		current->value = new_value;
	}
	else
		current->value = ft_strdup(value);
}
void	add_or_update_var(char *arg, char *key, char *value)
{
	t_env *current;

	current = find_env_var(global.env, key);
	if (current)
	{
		update_existing_var(current, arg, value);
	}
	else
	{
		add_envp(arg);
	}
}