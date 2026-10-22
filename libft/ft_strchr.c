/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:18:38 by finorako          #+#    #+#             */
/*   Updated: 2026/01/23 22:18:41 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *str, int c)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == (unsigned char)c)
			return ((char *)(str + index));
		index++;
	}
	if ((char)c == 0)
		return ((char *)(str + index));
	return (NULL);
}
