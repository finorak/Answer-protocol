/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:20:55 by finorako          #+#    #+#             */
/*   Updated: 2026/01/26 23:31:15 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	size_t	index;
	size_t	idx;

	if (*to_find == '\0')
		return ((char *)str);
	index = 0;
	while (str[index] && index < size)
	{
		idx = 0;
		while (str[index + idx] && index + idx < size
			&& str[index + idx] == to_find[idx]
			&& to_find[idx])
			idx++;
		if (to_find[idx] == '\0')
			return ((char *)(str + index));
		index++;
	}
	return (NULL);
}
