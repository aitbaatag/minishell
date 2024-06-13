/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 03:24:42 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 23:18:34 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	n;

	n = 0;
	i = 0;
	// if (!*dst || !*src)
	// 	return (0);
	while (src[i] != '\0')
	{
		i++;
	}
	if (size == 0)
		return (i);
	while (src[n] && n < size - 1)
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = '\0';
	return (i);
}
