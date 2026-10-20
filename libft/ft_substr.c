/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:21:30 by finorako          #+#    #+#             */
/*   Updated: 2026/01/29 11:08:58 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	index;
	size_t	src_len;
	char	*value;

	if (!str)
		return (NULL);
	src_len = ft_strlen(str);
	if (start >= src_len || len == 0)
		return (ft_strdup(""));
	if (len > src_len - start)
		len = src_len - start;
	index = 0;
	value = ft_calloc(len + 1, sizeof(char));
	if (!value)
		return (NULL);
	while (str[start + index] && index < len)
	{
		value[index] = str[start + index];
		index++;
	}
	return (value);
}
