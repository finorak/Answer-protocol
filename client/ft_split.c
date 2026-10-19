/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megalonia </var/spool/mail/megalonia>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 06:11:44 by megalonia         #+#    #+#             */
/*   Updated: 2026/10/19 06:20:36 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
* ex: hello world. sep = ' '
*/
static int	get_line(char *buffer, char sep)
{
	bool	start;
	int		counter;
	int		index;

	counter = 0;
	index = 0;
	while (buffer[index])
	{
		start = true;
		if (start && buffer[index] == sep)
			counter ++;
		while (buffer[index] == sep)
		{
			start = false;
			index ++;
		}
		index ++;
	}
	return (counter);
}

char	**ft_split(char *buffer, char sep)
{
	char	**value;
	int		index;
	int		len;

	len = get_line(buffer, sep);
	value = (char **)calloc(len + 1, sizeof(char *));
	if (!value)
		return (NULL);
	index = 0;
	while (index < len)
	{
		index ++;
	}
	printf("%d\n", len);
	value[index] = NULL;
	return (value);
}
