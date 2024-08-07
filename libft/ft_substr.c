/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 04:48:59 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:27:19 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = -1;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		ptr = safe_malloc(1);
		if (!ptr)
			return (NULL);
		ptr[0] = '\0';
		return (ptr);
	}
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	ptr = safe_malloc(1 + len * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[++i + start] && len > i)
	{
		ptr[i] = s[i + start];
	}
	ptr[i] = '\0';
	return (ptr);
}
