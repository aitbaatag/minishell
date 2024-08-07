/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 03:24:42 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/14 01:18:07 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	n;

	n = 0;
	i = 0;
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
