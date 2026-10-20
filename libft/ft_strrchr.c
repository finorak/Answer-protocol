/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:21:09 by finorako          #+#    #+#             */
/*   Updated: 2026/01/23 22:21:13 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	index;

	index = ft_strlen(str);
	while (index >= 0)
	{
		if (str[index] == (char)c)
			return ((char *)(str + index));
		index--;
	}
	return (NULL);
}
