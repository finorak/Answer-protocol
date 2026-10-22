/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:20:38 by finorako          #+#    #+#             */
/*   Updated: 2026/01/23 22:20:47 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	index;

	index = 0;
	while ((s1[index] || s2[index]) && index < size)
	{
		if (s1[index] != s2[index])
			return (((unsigned char)s1[index] - (unsigned char)s2[index]));
		index++;
	}
	return (0);
}
