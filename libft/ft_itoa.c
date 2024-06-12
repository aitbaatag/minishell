/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-baa <kait-baa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 03:03:00 by kait-baa          #+#    #+#             */
/*   Updated: 2024/06/12 16:26:37 by kait-baa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	get_digit(long i)
{
	size_t	n;

	n = 1;
	if (i < 0)
		i *= -1;
	while (i > 9)
	{
		i = i / 10;
		n++;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	size_t	len_digit;
	long	m;
	char	*ptr;

	m = n;
	len_digit = get_digit(m);
	if (m < 0)
	{
		m *= -1;
		len_digit++;
	}
	ptr = safe_malloc((len_digit + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[len_digit] = '\0';
	while (len_digit)
	{
		ptr[len_digit - 1] = m % 10 + 48;
		m /= 10;
		len_digit--;
	}
	if (n < 0)
		ptr[0] = '-';
	return (ptr);
}
