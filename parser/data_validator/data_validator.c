/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:53:10 by finorako          #+#    #+#             */
/*   Updated: 2026/10/17 09:39:44 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/parser.h"
#include "../../includes/world.h"

/*
* Extracting ids so that we can just verify
* the interconection of the rooms
*/
static char	*extract_room_id(char *room_id)
{
	char	*string;
	int		size;

	if (!room_id)
		return (NULL);
	size = strlen(room_id);
	string = (char *)calloc(size + 1, sizeof(char));
	if (!string)
		return (NULL);
	strncpy(string, room_id, size);
	return (string);
}

// Getting room id from the id given as parameter.
t_room	*get_room_from_id(t_all_rooms *container, char *id)
{
	char	*key;
	int		index;

	if (!container)
		return (NULL);
	index = 0;
	while (index < container->len)
	{
		key = container->rooms[index]->id;
		if (strcmp(key, id) == 0)
			return (container->rooms[index]);
		index += 1;
	}
	return (NULL);
}

// Might remove this later on as I don't really
// understand why I created this function ?
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
static char	**get_ids(t_world *data, char **ids)
{
	t_room	*current_room;
	int		index;

	if (!data)
		return (NULL);
	index = 0;
	while (index < data->rooms->len)
	{
		current_room = data->rooms->rooms[index];
		ids[index] = extract_room_id(current_room->id);
		if (!ids[index])
		{
			custom_free(ids, index, TYPE_STRING_TABLE);
			return (NULL);
		}
		index++;
	}
	ids[index] = NULL;
	return (key_verifier(ids, index, "none"));
}

//	VALIDATE data.
//			- count how many time we enter a room
//			- return `true` if count >= COUNTER (`8`)
//				else `false`
bool	data_validator(t_world *data)
{
	t_stack	*stack;
	char	*room_ids[MAX_ID_LEN];
	bool	valid;
	int		room_len;

	if (!data || !data->extract)
		return (false);
	get_ids(data, room_ids);
	valid = true;
	stack = new_stack(get_room_from_id(data->rooms, *room_ids));
	if (!stack)
		return (false);
	room_len = data->rooms->len;
	if (!verify_exit(data, room_ids)
		|| !interconnection_checker(&stack, data->rooms, room_ids)
	)
	{
		valid = false;
		free(stack);
		fprintf(stdout, "Room doesn't interconnect or \
room doesn't exist\n");
		free_data(data, NULL, true);
	}
	custom_free(room_ids, room_len, TYPE_STRING_TABLE);
	return (valid);
}
