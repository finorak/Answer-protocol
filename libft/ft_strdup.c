/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:18:57 by finorako          #+#    #+#             */
/*   Updated: 2026/01/23 22:18:59 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		index;
	char	*dest;

	index = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dest)
		return (NULL);
	while (str[index])
	{
		dest[index] = str[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
