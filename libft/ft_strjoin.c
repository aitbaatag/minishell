/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadiqui <asadiqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 05:10:06 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/13 03:57:33 by asadiqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	size_t	ss1;
	size_t	ss2;

	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	ss1 = ft_strlen(s1);
	ss2 = ft_strlen(s2);
	str = safe_malloc((ss1 + ss2) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (*s1)
	{
		*(str + i) = *s1++;
		i++;
	}
	while (*s2)
	{
		*(str + i) = *s2++;
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
