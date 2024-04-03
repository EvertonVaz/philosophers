/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeraldo <egeraldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 19:44:18 by egeraldo          #+#    #+#             */
/*   Updated: 2023/07/25 19:58:26 by egeraldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapi;
	unsigned int	i;
	size_t			len;

	if (s == NULL)
		return (NULL);
	mapi = (char *)ft_calloc((len = ft_strlen(s)) + 1, sizeof(char));
	if (mapi == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		mapi[i] = f(i, s[i]);
	return (mapi);
}
