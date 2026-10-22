/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:18:28 by finorako          #+#    #+#             */
/*   Updated: 2026/01/29 16:35:19 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	move_idx(char const *str, char c, size_t *idx, size_t *start)
{
	while (str[*idx] && str[*idx] == c)
		*idx += 1;
	*start = *idx;
	while (str[*idx] && str[*idx] != c)
		*idx += 1;
}

static void	free_all(char **value, int size)
{
	int	index;

	index = 0;
	while (value[index] && index < size)
	{
		free(value[index]);
		index++;
	}
	free(value);
}

static int	count_word(char const *str, char c)
{
	int	counter;
	int	index;
	int	start_count;

	counter = 0;
	index = 0;
	while (str[index])
	{
		start_count = 0;
		while (str[index] && str[index] == c)
			index++;
		while (str[index] && str[index] != c)
		{
			start_count = 1;
			index++;
		}
		if (start_count)
			counter++;
	}
	return (counter);
}

char	**ft_split(char const *str, char c)
{
	int		word_count;
	size_t	index;
	char	**value;
	size_t	start;
	int		value_idx;

	index = 0;
	value_idx = 0;
	word_count = count_word(str, c);
	value = ft_calloc(word_count + 1, sizeof(char *));
	if (!value)
		return (NULL);
	while (str[index] && value_idx < word_count)
	{
		move_idx(str, c, &index, &start);
		value[value_idx] = ft_substr(str, start, index - start);
		if (!value[value_idx])
		{
			free_all(value, value_idx);
			return (NULL);
		}
		value_idx++;
	}
	value[value_idx] = NULL;
	return (value);
}
