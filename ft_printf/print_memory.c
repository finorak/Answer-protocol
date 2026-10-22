/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:45:30 by finorako          #+#    #+#             */
/*   Updated: 2026/02/09 13:17:28 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include "ft_printf.h"

static void	print_hex(uintptr_t number, char delimiter, int *counter)
{
	uintptr_t	c;

	if (number >= 16)
		print_hex(number / 16, delimiter, counter);
	c = number % 16;
	if (c < 10)
		c += '0';
	else
		c += delimiter - 10;
	ft_putchar(c);
	*counter += 1;
}

void	print_memory(void *add, int *counter)
{
	uintptr_t	str;

	if (add == NULL)
	{
		print_str("(nil)", counter);
		return ;
	}
	print_str("0x", counter);
	str = (uintptr_t)add;
	print_hex(str, 'a', counter);
}
