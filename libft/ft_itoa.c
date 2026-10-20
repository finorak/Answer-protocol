/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:16:00 by finorako          #+#    #+#             */
/*   Updated: 2026/01/29 16:39:03 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdlib.h>

static int	ft_intlen(int *n, int *stop)
{
	int	counter;
	int	temp;

	counter = 0;
	*stop = 0;
	temp = *n;
	if (temp < 0)
	{
		counter++;
		temp = -temp;
		*n = -(*n);
		*stop = 1;
	}
	while (temp > 0)
	{
		temp = temp / 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*value;
	int		len;
	int		stop;
	int		temp;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	temp = n;
	len = ft_intlen(&n, &stop);
	value = (char *)malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	value[len] = '\0';
	len--;
	if (temp < 0)
		value[0] = '-';
	while (len >= stop && n)
	{
		value[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (value);
}
