/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:17:29 by finorako          #+#    #+#             */
/*   Updated: 2026/01/27 08:19:48 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t size)
{
	size_t			index;
	unsigned char	*dest;

	dest = s;
	index = 0;
	while (index < size)
	{
		dest[index] = c;
		index++;
	}
	return (dest);
}
