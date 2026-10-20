/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:16:42 by finorako          #+#    #+#             */
/*   Updated: 2026/01/29 16:32:41 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t size)
{
	unsigned char	*src;
	size_t			index;

	index = 0;
	src = (unsigned char *)s;
	while (index < size)
	{
		if (src[index] == (unsigned char)c)
			return (&src[index]);
		index++;
	}
	return (NULL);
}
