/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 10:02:49 by finorako          #+#    #+#             */
/*   Updated: 2026/02/09 10:18:55 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(unsigned int number, char delimiter, int *counter)
{
	char	c;

	if (number >= 16)
		ft_puthex(number / 16, delimiter, counter);
	c = number % 16;
	if (c < 10)
		c += '0';
	else
		c += delimiter - 10;
	ft_putchar(c);
	*counter += 1;
}
