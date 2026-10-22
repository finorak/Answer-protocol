/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:55:04 by finorako          #+#    #+#             */
/*   Updated: 2026/02/09 10:21:50 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_unsigned(unsigned int number, int *counter)
{
	if (number >= 10)
		print_unsigned(number / 10, counter);
	ft_putchar((number % 10) + '0');
	*counter += 1;
}
