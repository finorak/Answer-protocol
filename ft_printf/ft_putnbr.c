/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:27:13 by finorako          #+#    #+#             */
/*   Updated: 2026/02/09 09:46:26 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

void	ft_putnbr(int number, int *counter)
{
	if (number == INT_MIN)
	{
		print_str("-2147483648", counter);
		return ;
	}
	if (number < 0)
	{
		ft_putchar('-');
		*counter += 1;
		number = -number;
	}
	if (number >= 10)
		ft_putnbr(number / 10, counter);
	ft_putchar((number % 10) + '0');
	*counter += 1;
}
