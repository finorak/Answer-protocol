/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:11:19 by finorako          #+#    #+#             */
/*   Updated: 2026/01/29 16:57:17 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(int c)
{
	return ((8 <= c && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	int	value;
	int	signe;

	value = 0;
	signe = 1;
	while (*str && is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		value = (value * 10) + (*str - '0');
		str++;
	}
	return (value * signe);
}
