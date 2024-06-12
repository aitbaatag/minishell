/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 03:50:52 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:28:26 by kait-baa         ###   ########.fr       */
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
