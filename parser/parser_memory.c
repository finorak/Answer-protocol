/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 14:25:05 by finorako          #+#    #+#             */
/*   Updated: 2026/09/30 19:40:21 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../includes/parser.h"

void	free_rooms(t_all_rooms *rooms, int size)
{
	int	index;

	if (!rooms)
		return ;
	index = 0;
	while (index < size)
	{
		free(rooms->rooms[index]);
		index += 1;
	}
	free(rooms);
}

void	free_items(t_all_items *items, int size)
{
	int	index;

	if (!items)
		return ;
	index = 0;
	while (index < size)
	{
		free(items->items[index]);
		index ++;
	}
	free(items);
}

void	free_npcs(t_all_npcs *items, int size)
{
	int	index;

	if (!items)
		return ;
	index = 0;
	while (index < size)
	{
		free(items->npcs[index]);
		index ++;
	}
	free(items);
}

void	free_data(t_data *data, char *buffer)
{
	if (buffer)
		free(buffer);
	if (data->rooms)
		free_rooms(data->rooms, data->rooms->len);
	if (data->items)
		free_items(data->items, data->items->len);
	if (data->npcs)
		free_npcs(data->npcs, data->npcs->len);
	if (data)
		free(data);
}
