/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:50:52 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/13 04:54:27 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup(const char *string)
{
	size_t	i;
	char	*ptr;
	int		n;

	n = 0;
	i = 0;
	if (!string)
		return (NULL);
	i = ft_strlen(string);
	ptr = (char *)safe_malloc(1 + i * sizeof(char));
	if (!ptr)
		return (NULL);
	while (string[n])
	{
		ptr[n] = string[n];
		n++;
	}
	ptr[n] = '\0';
	return (ptr);
}
