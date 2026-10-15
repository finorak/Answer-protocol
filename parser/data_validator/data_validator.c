/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:53:10 by finorako          #+#    #+#             */
/*   Updated: 2026/10/15 16:12:34 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/world.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Getting room id from the id given as parameter.
t_room	*get_room_from_id(t_all_rooms *container, char *id)
{
	int	index;

	if (!container)
		return (NULL);
	index = 0;
	while (index < container->len)
	{
		if (strcmp(container->rooms[index]->id, id) == 0)
			return (container->rooms[index]);
		index += 1;
	}
	return (NULL);
}

static char	**key_verifier(char **keys, int size, char *to_cmp)
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
		index++;
	}
	return (keys);
}

// Extract all the room ids to verify if the
// exist id is in the room.
static char	**get_room_ids(t_data *data)
{
	t_room	*current_room;
	char	**room_ids;
	int		index;

	if (!data)
		return (NULL);
	if (!data->rooms)
		return (NULL);
	room_ids = (char **)calloc(data->rooms->len + 1, sizeof(char *));
	if (!room_ids)
		return (NULL);
	index = 0;
	while (index < data->rooms->len)
	{
		current_room = data->rooms->rooms[index];
		room_ids[index] = extract_room_id(current_room->id);
		if (!room_ids[index])
		{
			custom_free(room_ids, index, TYPE_STRING_TABLE);
			return (NULL);
		}
		index++;
	}
	room_ids[index] = NULL;
	return (key_verifier(room_ids, index, "none"));
}

//			- count how many time we enter a room
//			- return `true` if count >= COUNTER (`8`)
//				else `false`
bool	data_validator(t_data *data)
{
	t_stack	*stack;
	char	**room_ids;
	bool	valid;
	int		counter;

	if (!data || !data->extract)
		return (false);
	room_ids = get_room_ids(data);
	if (!room_ids)
		return (false);
	valid = true;
	counter = 0;
	stack = new_stack(get_room_from_id(data->rooms, *room_ids));
	if (!interconnection_checker(&stack, data->rooms, room_ids, &counter))
		valid = false;
	custom_free(room_ids, data->rooms->len, TYPE_STRING_TABLE);
	return (valid);
}
