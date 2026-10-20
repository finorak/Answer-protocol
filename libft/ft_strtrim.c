/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:20:43 by finorako          #+#    #+#             */
/*   Updated: 2026/01/29 17:03:55 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	index_start(const char *str, const char *set, size_t *start)
{
	size_t	index;

	index = 0;
	*start = 0;
	while (str[index] && ft_strrchr(set, str[index]))
		index++;
	*start = index;
	return (index);
}

static size_t	index_stop(const char *str, const char *set)
{
	size_t	index;

	index = ft_strlen(str) - 1;
	while (index > 0 && str[index] && ft_strrchr(set, str[index]))
		index--;
	return (index);
}

char	*ft_strtrim(const char *str, const char *set)
{
	char	*value;
	size_t	index;
	size_t	stop;
	int		value_idx;

	if ((str == NULL && set == NULL) || str == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(str));
	value_idx = 0;
	stop = index_stop(str, set);
	if (stop == 0)
		return (ft_strdup(""));
	value = ft_calloc(stop - index_start(str, set, &index) + 2, sizeof(char));
	if (!value)
		return (NULL);
	while (str[index] && index <= stop)
	{
		value[value_idx] = str[index];
		index++;
		value_idx++;
	}
	return (value);
}
