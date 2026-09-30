/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_extractor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 14:53:07 by finorako          #+#    #+#             */
/*   Updated: 2026/09/30 16:49:28 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/data_extractor.h"
#include "../../includes/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: IMPLEMENT MEMORY MANAGEMENT IN CASE OF MEMROY ERRORS.
t_room	*extract_room_from_key(char *key, cJSON *room_json, t_room *room)
{
	t_world_content	content;

	if (!room_json || !room)
		return (NULL);
	content.name = cJSON_GetObjectItemCaseSensitive(room_json, "name");
	if (!cJSON_IsString(content.name) && content.name->valuestring == NULL)
		return (NULL);
	strncpy(room->name, content.name->valuestring, BUFFER_SIZE);
	content.desc = cJSON_GetObjectItemCaseSensitive(room_json, "description");
	if (!cJSON_IsString(content.desc) && !content.desc->valuestring)
		return (NULL);
	strncpy(room->description, content.desc->valuestring, BUFFER_SIZE);
	strncpy(room->id, key, BUFFER_SIZE);
	content.exits = cJSON_GetObjectItemCaseSensitive(room_json, "exits");
	if (!cJSON_IsArray(content.exits))
		return (NULL);
	if (!traverse_array(content.exits, room, "exits"))
		return (NULL);
	content.npcs = cJSON_GetObjectItemCaseSensitive(room_json, "npcs");
	if (!traverse_array(content.npcs, room, "npcs"))
		return (NULL);
	content.items = cJSON_GetObjectItemCaseSensitive(room_json, "items");
	if (!traverse_array(content.items, room, "items"))
		return (NULL);
	return (room);
}

// TODO: LOOK AT WHY NORMINETTE IS COMPLAINING.
static t_all_rooms	*get_rooms(cJSON *world_json, t_all_rooms *rooms_container)
{
	if (!world_json)
		return (NULL);
	if (!traverse_room_object(world_json, rooms_container))
		return (false);
	return (rooms_container);
}

t_all_rooms	*extract_rooms(cJSON *root, char *buffer)
{
	t_all_rooms	*rooms_container;
	cJSON		*rooms_json;

	if (!buffer)
	{
		return (NULL);
	}
	rooms_container = (t_all_rooms *)malloc(sizeof(t_all_rooms));
	if (!rooms_container)
		return (NULL);
	rooms_json = cJSON_GetObjectItemCaseSensitive(root, ROOM_KEY);
	if (!rooms_json)
	{
		free(rooms_container);
		return (NULL);
	}
	if (!cJSON_IsObject(rooms_json))
	{
		fprintf(stderr, "'%s' key not found or is not an object\n", ROOM_KEY);
		free(rooms_container);
		cJSON_Delete(rooms_json);
		return (NULL);
	}
	return (get_rooms(rooms_json, rooms_container));
}
