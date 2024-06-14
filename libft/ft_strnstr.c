/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 01:18:29 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/14 08:28:31 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	b;

	i = 0;
	if (!s1 && !n)
		return (NULL);
	if (!*s2)
		return ((char *)s1);
	while (s1[i] && n > i)
	{
		b = 0;
		while (s1[i + b] == s2[b] && n > i + b)
		{
			b++;
			if (s2[b] == '\0')
				return ((char *)s1 + i);
		}
		i++;
	}
	return (NULL);
}
