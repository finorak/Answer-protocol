/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:27:24 by finorako          #+#    #+#             */
/*   Updated: 2026/09/28 15:03:39 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 2)
	{
		printf("Lanch with the command ./server <config.json>");
		return (1);
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (!init_data(data, argv[1]))
	{
		printf("Error on initializing data\n");
		return (1);
	}
	return (0);
}
