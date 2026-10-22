/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:20:29 by finorako          #+#    #+#             */
/*   Updated: 2026/01/27 08:20:58 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char			*value;
	unsigned int	index;

	if (!str || !f)
		return (NULL);
	value = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!value)
		return (NULL);
	index = 0;
	while (str[index])
	{
		value[index] = f(index, str[index]);
		index++;
	}
	return (value);
}
