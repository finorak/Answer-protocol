/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:17:17 by finorako          #+#    #+#             */
/*   Updated: 2026/01/27 10:18:55 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char		*d;
	unsigned const char	*s;
	size_t				index;

	d = dest;
	s = src;
	index = 0;
	while (index < size)
	{
		d[index] = s[index];
		index++;
	}
	return (dest);
}
