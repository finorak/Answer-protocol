/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:17:01 by finorako          #+#    #+#             */
/*   Updated: 2026/01/29 17:01:46 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	unsigned const char	*data1;
	unsigned const char	*data2;
	size_t				index;

	index = 0;
	data1 = (unsigned const char *)s1;
	data2 = (unsigned const char *)s2;
	while (index < size)
	{
		if (data1[index] != data2[index])
			return (data1[index] - data2[index]);
		index++;
	}
	return (0);
}
