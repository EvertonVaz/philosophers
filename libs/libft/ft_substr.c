/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:55:41 by egeraldo          #+#    #+#             */
/*   Updated: 2024/01/17 10:54:17 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;

	slen = ft_strlen(s);
	if (s == NULL || start > slen)
		return (ft_strdup(""));
	if (slen - start >= len)
		substr = (char *)ft_calloc(len + 1, sizeof(char));
	else
	{
		substr = (char *)ft_calloc(slen - start + 1, sizeof(char));
		len = slen - start + 1;
	}
	s += start;
	if (substr == NULL)
		return (NULL);
	else
		ft_strlcpy(substr, s, (len + 1));
	return (substr);
}
