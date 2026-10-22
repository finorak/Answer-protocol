/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:44:31 by finorako          #+#    #+#             */
/*   Updated: 2026/02/09 09:58:47 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include "ft_printf.h"

void	ft_putchar(char c)
{
	static pthread_mutex_t	g_mutex;
	static bool				initialized = false;

	if (!initialized)
	{
		pthread_mutex_init(&g_mutex, NULL);
		initialized = true;
	}
	pthread_mutex_lock(&g_mutex);
	write(1, &c, 1);
	pthread_mutex_unlock(&g_mutex);
}

void	print_str(char *str, int *counter)
{
	int	index;

	if (str == NULL)
	{
		print_str(NULL_MESSAGE, counter);
		return ;
	}
	index = 0;
	while (str[index])
	{
		ft_putchar(str[index]);
		*counter += 1;
		index++;
	}
}
