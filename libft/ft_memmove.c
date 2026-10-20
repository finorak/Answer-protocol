/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:10:58 by finorako          #+#    #+#             */
/*   Updated: 2026/01/29 17:01:23 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned const char	*s;
	unsigned char		*d;

	d = dest;
	s = src;
	if (d > s)
	{
		while (size--)
			d[size] = s[size];
	}
	else
		ft_memcpy(dest, src, size);
	return (dest);
}
