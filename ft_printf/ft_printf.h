/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:53:24 by finorako          #+#    #+#             */
/*   Updated: 2026/02/09 14:35:40 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# define NULL_MESSAGE "(null)"
# include <stdarg.h>

typedef struct s_start
{
	va_list	arg;
	int		index;
	int		counter;
}				t_start;

int				ft_printf(const char *str, ...);

void			ft_putnbr(int number, int *counter);

void			ft_putchar(char c);

void			print_str(char *str, int *counter);

size_t			ft_strlen(const char *str);

void			ft_puthex(unsigned int number, char c, int *counter);

void			print_unsigned(unsigned int number, int *counter);

void			print_memory(void *add, int *counter);
#endif
