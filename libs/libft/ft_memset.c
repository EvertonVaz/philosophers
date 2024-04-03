/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:25:33 by egeraldo          #+#    #+#             */
/*   Updated: 2023/07/18 14:44:12 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int value, size_t n)
{
	char	*ptr;

	ptr = (char *)src;
	while (n--)
		*ptr++ = (unsigned char)value;
	return ((void *)src);
}
