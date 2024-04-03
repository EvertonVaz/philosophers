/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:42:08 by egeraldo          #+#    #+#             */
/*   Updated: 2024/02/27 15:56:03 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numlen(int n)
{
	size_t	i;

	i = 1;
	n /= 10;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*result;
	size_t		digits;
	long int	num;

	num = n;
	digits = ft_numlen(n);
	if (num < 0)
	{
		num = -num;
		digits++;
	}
	result = (char *)ft_calloc(digits + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	while (digits-- > 0)
	{
		result[digits] = '0' + (num % 10);
		num /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
