/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:27:24 by finorako          #+#    #+#             */
/*   Updated: 2026/09/30 10:27:35 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/world.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_buffer_store	buffer;
	t_data			*data;

	if (argc != 2)
	{
		fprintf(stderr, "Lanch with ./server <config.txt>");
		return (1);
	}
	buffer.buffer_size = get_buffer_size(argv[1]);
	buffer.buffer = get_buffer(argv[1], buffer.buffer_size);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return (1);
	}
	if (!init_world_data(data, buffer.buffer))
	{
		fprintf(stderr, "Error\n");
		return (1);
	}
	free_data(data, buffer.buffer);
	return (0);
}
