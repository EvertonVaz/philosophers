/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:15:14 by egeraldo          #+#    #+#             */
/*   Updated: 2023/07/20 14:59:05 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp_dest;
	unsigned char	*temp_src;

	temp_dest = (unsigned char *)dest;
	temp_src = (unsigned char *)src;
	if (temp_dest == NULL && temp_src == NULL)
		return (NULL);
	if (temp_dest < temp_src)
		return (ft_memcpy(temp_dest, temp_src, n));
	else
	{
		while (n--)
			((unsigned char *)temp_dest)[n] = ((unsigned char *)temp_src)[n];
		return (temp_dest);
	}
}
