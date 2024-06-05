#include "../include/minishell.h"

char	*handle_questionmark(char *var_name)
{
	char	*buff;
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (var_name[i++] == '?')
	{
		tmp = ft_itoa(get_exit_status());
		len += ft_strlen(tmp);
		while (var_name[i])
		{
			len++;
			i++;
		}
		buff = safe_malloc(sizeof(char) * (len + 1));
		ft_strlcpy(buff, tmp, ft_strlen(tmp) + 1);
		ft_strlcpy(buff + ft_strlen(tmp), var_name + 1, ft_strlen(var_name)
				+ 1);
		free(tmp);
	}
	else
	{
		while (var_name[i] && var_name[i] != '?')
			i++;
		buff = safe_malloc(sizeof(char) * (ft_strlen(var_name) - i + 1));
		ft_strlcpy(buff, var_name + i, ft_strlen(var_name) - i + 1);
	}
	return (buff);
}

void	expand(char **args)
{
	char *var_name;
	char *var_value;
	t_env *tmp;
	int i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$' && args[i][1])
		{
			var_name = ft_substr(args[i], 1, ft_strlen(args[i]) - 1);
			free(args[i]);
			tmp = find_env_var(global.env, var_name);
			if (tmp)
				var_value = tmp->value;
			else
				var_value = handle_questionmark(var_name);
			args[i] = safe_malloc(sizeof(char) * (ft_strlen(var_value) + 1));
			ft_strlcpy(args[i], var_value, ft_strlen(var_value) + 1);
			free(var_name);
			if (!tmp)
				free(var_value);
		}
		i++;
	}
}