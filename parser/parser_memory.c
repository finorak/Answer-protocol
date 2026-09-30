/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 14:25:05 by finorako          #+#    #+#             */
/*   Updated: 2026/09/28 14:26:21 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/parser.h"

void	free_rooms(t_all_rooms *rooms)
{
	int	index;

	if (!rooms)
		return ;
	index = 0;
	while (index < rooms->len)
	{
		free(rooms->rooms[index]);
		index += 1;
	}
	free(rooms);
}

void	free_data(t_data *data, char *buffer)
{
	if (buffer)
		free(buffer);
	if (data->rooms)
		free_rooms(data->rooms);
	if (data)
		free(data);
}
