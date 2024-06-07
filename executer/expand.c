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

int	var_len(char *var)
{
	int	len;

	len = 0;
	while (var[len] && ft_isalnum(var[len]))
		len++;
	return (len);
}

void	expand(char **args)
{
	char 	*var_name;
	char 	*var_value;
	int		len;
	char	*buff;
	char	*tmp_buff;
	t_env	*tmp;
	int 	i;
	int		j;

	buff = NULL;
	i = 1;
	while (args[i])
	{
		printf("args: %s\n", args[i]);
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '$' && args[i][j + 1])
			{
				len = var_len(args[i] + j + 1);
				var_name = ft_substr(args[i], j + 1, len);
				// free(args[i]);
				tmp = find_env_var(global.env, var_name);
				if (tmp)
					var_value = tmp->value;
				else
					var_value = handle_questionmark(var_name);
				tmp_buff = safe_malloc(sizeof(char) * (ft_strlen(var_value) + 1));
				ft_strlcpy(tmp_buff, var_value, ft_strlen(var_value) + 1);
				// free(var_name);
				// if (!tmp)
					// free(var_value);
				j += len;
				if (!buff)
					buff = tmp_buff;
				else
					buff = ft_strjoin(buff, tmp_buff);
			}
			else
			{
				char *single_char = malloc(2);
				single_char[0] = args[i][j];
				single_char[1] = '\0';
				if (!buff)
					buff = single_char;
				else
					buff = ft_strjoin(buff, single_char);
			}
			j++;
		}
		args[i] = remove_quotes(buff);
		buff = NULL;
		i++;
	}
}