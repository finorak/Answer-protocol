/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:53:10 by finorako          #+#    #+#             */
/*   Updated: 2026/10/11 16:25:54 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../includes/parser.h"
#include "../../includes/world.h"

static char **key_verifier(char **keys, int size, char *to_cmp)
{
	int	index;

	if (!keys)
		return (NULL);
	index = 0;
	while (index < size)
	{
		if (strcmp(keys[index], to_cmp) == 0)
		{
			custom_free(keys, size, TYPE_STRING_TABLE);
			return (NULL);
		}
		index ++;
	}
	return (keys);
}

static char	**get_room_ids(t_data *data)
{
	t_all_rooms	*room_container;
	t_room		*current_room;
	char		**room_ids;
	int			index;

	if (!data)
		return (NULL);
	room_container = data->rooms;
	if (!room_container || !*room_container->rooms)
		return (NULL);
	room_ids = (char **)calloc(room_container->len + 1, sizeof(char *));
	if (!room_ids)
		return (NULL);
	index = 0;
	while (index < room_container->len)
	{
		current_room = room_container->rooms[index];
		room_ids[index] = extract_room_id(current_room->id);
		if (!room_ids[index])
		{
			custom_free(room_ids, index, TYPE_STRING_TABLE);
			return (NULL);
		}
		index ++;
	}
	room_ids[index] = NULL;
	return (key_verifier(room_ids, index, "none"));
}

// verify if at least 8 room do intersect
// get current exits
// verify each exit is a room key or is none
bool	data_validator(t_data *data)
{
	t_room	*current_room;
	char	**room_ids;
	int		index;

	if (!data || !data->extract)
		return (false);
	room_ids = get_room_ids(data);
	if (!room_ids)
		return (false);
	index = 0;
	while (index < data->rooms->len)
	{
		// verify if the key is inside exits
		current_room = data->rooms->rooms[index];
		printf("%s\n", room_ids[index]);
		key_is_reconnecting(current_room->id, current_room->exits);
		index++;
	}
	custom_free(room_ids, index, TYPE_STRING_TABLE);
	return (true);
}
