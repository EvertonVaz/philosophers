/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etovaz <etovaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:59:36 by egeraldo          #+#    #+#             */
/*   Updated: 2024/03/09 15:17:02 by etovaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_str(int free_which_str, const char *s1, const char *s2)
{
	if (free_which_str == 1)
		free((void *)s1);
	else if (free_which_str == 2)
		free((void *)s2);
	else if (free_which_str == 3)
	{
		free((void *)s1);
		free((void *)s2);
	}
}

char	*ft_strjoin(char const *s1, char const *s2, int free_which_str)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (s1 && !s2)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)ft_calloc(len, sizeof(char));
	if (join == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		join[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		join[i++] = s2[j];
	join[i] = '\0';
	free_str(free_which_str, s1, s2);
	return (join);
}
