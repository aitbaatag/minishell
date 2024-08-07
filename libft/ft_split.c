/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:19:25 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:26:40 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_char(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] != c)
	{
		while (str[i] != c && str[i])
		{
			i++;
		}
		return (i);
	}
	else
		return (0);
}

static int	count_words(char *ptr, char c)
{
	int	word_size;

	word_size = 0;
	while (*ptr)
	{
		while (*ptr == c)
		{
			ptr++;
		}
		if (*ptr)
			word_size++;
		while (*ptr && *ptr != c)
			ptr++;
	}
	return (word_size);
}

static char	**help_split(char const *s, char c, char **ptr)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		i = count_char((char *)s, c);
		if (i != 0)
		{
			ptr[j] = ft_substr(s, 0, i);
			if (!ptr[j])
				return (NULL);
			j++;
		}
		s += i;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		word_size;

	if (!s)
		return (NULL);
	word_size = count_words((char *)s, c);
	ptr = (char **)safe_malloc(sizeof(char *) * (word_size + 1));
	if (!ptr)
		return (NULL);
	ptr[word_size] = NULL;
	ptr = help_split((char *)s, c, ptr);
	return (ptr);
}
