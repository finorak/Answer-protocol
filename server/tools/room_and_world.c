/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_and_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:27:53 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 09:55:42 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"
#include <stdio.h>

t_room	*get_room_by_id(char *room_id, t_world *world)
{
	int	i;

	i = -1;
	while (++i < MAX_LIST_LEN)
	{
		if (!strcmp(world->rooms->rooms[i]->id, room_id))
			return (world->rooms->rooms[i]);
	}
	return (NULL);
}

t_room	*get_room_by_player_fd(int client_fd, t_world *world)
{
	int	i;
	int	j;

	i = -1;
	printf("%d\n", world->rooms->len);
	while (++i < world->rooms->len)
	{
		j = -1;
		while (++j < world->rooms->rooms[i]->players.len)
		{
			if (atoi(world->rooms->rooms[i]->players.ids[j]) == client_fd)
				return (world->rooms->rooms[i]);
		}
	}
	return (NULL);
}

t_room	*get_room_by_item_id(char *item_id, t_world *world)
{
	int	i;
	int	j;

	i = -1;
	while (++i < world->rooms->len)
	{
		j = -1;
		while (++j < world->rooms->rooms[i]->items.len)
		{
			if (!strcmp((world->rooms->rooms[i]->items.ids[j]), item_id))
				return (world->rooms->rooms[i]);
		}
	}
	return (NULL);
}

t_room	*get_room_by_npc_id(char *npc_id, t_world *world)
{
	int	i;
	int	j;

	i = -1;
	while (++i < world->rooms->len)
	{
		j = -1;
		while (++j < world->rooms->rooms[i]->npcs.len)
		{
			if (!strcmp(world->rooms->rooms[i]->npcs.ids[j], npc_id))
				return (world->rooms->rooms[i]);
		}
	}
	return (NULL);
}
