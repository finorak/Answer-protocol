/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:19:16 by finorako          #+#    #+#             */
/*   Updated: 2026/01/23 22:19:22 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join(char *dest, const char *src, size_t *curr_idx)
{
	size_t			src_idx;

	src_idx = 0;
	while (src[src_idx])
	{
		dest[*curr_idx] = src[src_idx];
		src_idx++;
		*curr_idx += 1;
	}
	dest[*curr_idx] = '\0';
	return (dest);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*value;
	size_t	index;
	size_t	len;

	if (s1 == NULL && s2)
		return (ft_strdup(s2));
	else if (s1 && s2 == NULL)
		return (ft_strdup(s1));
	else if (s1 == NULL && s2 == NULL)
		return (NULL);
	index = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	value = ft_calloc(len + 1, sizeof(char));
	if (!value)
		return (NULL);
	join(value, s1, &index);
	join(value, s2, &index);
	value[index] = '\0';
	return (value);
}
