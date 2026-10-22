/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:54:39 by finorako          #+#    #+#             */
/*   Updated: 2026/02/09 14:35:30 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <pthread.h>
#include "ft_printf.h"

void	print_arg(const char *str, va_list *arg, int index, int *counter)
{
	if (str[index] == 'd' || str[index] == 'i')
		ft_putnbr(va_arg(*arg, int), counter);
	else if (str[index] == 's')
		print_str(va_arg(*arg, char *), counter);
	else if (str[index] == 'c')
	{
		ft_putchar(va_arg(*arg, int));
		*counter += 1;
	}
	else if (str[index] == 'x')
		ft_puthex(va_arg(*arg, int), 'a', counter);
	else if (str[index] == 'X')
		ft_puthex(va_arg(*arg, int), 'A', counter);
	else if (str[index] == 'u')
		print_unsigned(va_arg(*arg, unsigned int), counter);
	else if (str[index] == 'p')
		print_memory(va_arg(*arg, void *), counter);
	else if (str[index] == '%')
	{
		ft_putchar(str[index]);
		*counter += 1;
	}
}

int	ft_printf(const char *str, ...)
{
	t_start	start;

	va_start(start.arg, str);
	start.index = 0;
	start.counter = 0;
	while (str[start.index])
	{
		if (str[start.index] == '%')
		{
			start.index++;
			print_arg(str, &start.arg, start.index, &start.counter);
			start.index++;
		}
		else
		{
			ft_putchar(str[start.index++]);
			start.counter += 1;
		}
	}
	va_end(start.arg);
	return (start.counter);
}
