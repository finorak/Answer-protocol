/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:11:41 by finorako          #+#    #+#             */
/*   Updated: 2026/01/29 15:26:19 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

void	*ft_calloc(size_t num_el, size_t size)
{
	void	*value;
	size_t	data_size;

	if (size == 0 || num_el == 0)
		return (malloc(1));
	if (num_el > SIZE_MAX / size)
		return (NULL);
	data_size = num_el * size;
	value = malloc(data_size);
	if (!value)
		return (NULL);
	ft_bzero(value, data_size);
	return (value);
}
