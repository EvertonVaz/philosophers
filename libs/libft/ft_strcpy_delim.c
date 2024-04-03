/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_delim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:03:24 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/12 12:12:42 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy_delim(const char *src, char delim)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_calloc(sizeof(char), (ft_strlen(src) + 1));
	while (src && src[i] && src[i] != delim)
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
