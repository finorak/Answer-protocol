/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_extractor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 14:53:07 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 15:49:22 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/data_extractor.h"
#include "../../includes/parser.h"
#include <stdio.h>

static t_room	*get_room(cJSON *content, const cJSON *room_json, t_room *room)
{
	content = cJSON_GetObjectItemCaseSensitive(room_json, "items");
	room->exits.len = 0;
	if (!content || !traverse_room_array(content, room, "items"))
		return (free(room), NULL);
	return (room);
}

// TODO: IMPLEMENT MEMORY MANAGEMENT IN CASE OF MEMROY ERRORS.
t_room	*extract_room_from_key(
	const char *key, const cJSON *room_json, t_room *room)
{
	cJSON	*content;

	if (!room_json || !room)
		return (free(room), NULL);
	content = cJSON_GetObjectItemCaseSensitive(room_json, "name");
	if (!content || !cJSON_IsString(content) || !content->valuestring)
		return (free(room), NULL);
	strncpy(room->name, content->valuestring, MAX_NAME_LEN);
	content = cJSON_GetObjectItemCaseSensitive(room_json, "description");
	if (!content || !cJSON_IsString(content) || !content->valuestring)
		return (free(room), NULL);
	strncpy(room->description, content->valuestring, MAX_DESCRIPTION_LEN);
	strncpy(room->id, key, MAX_ID_LEN);
	content = cJSON_GetObjectItemCaseSensitive(room_json, "exits");
	if (!content || !cJSON_IsArray(content))
		return (free(room), NULL);
	if (!content || !traverse_room_array(content, room, "exits"))
		return (free(room), NULL);
	content = cJSON_GetObjectItemCaseSensitive(room_json, "npcs");
	if (!content || !traverse_room_array(content, room, "npcs"))
		return (free(room), NULL);
	return (get_room(content, room_json, room));
}

// TODO: LOOK AT WHY NORMINETTE IS COMPLAINING.
static t_all_rooms	*get_rooms(
	const cJSON *room_json, t_all_rooms *rooms_container)
{
	if (!room_json)
		return (NULL);
	rooms_container->len = 0;
	if (!traverse_room_object(room_json, rooms_container))
		return (NULL);
	return (rooms_container);
}

t_all_rooms	*extract_rooms(const cJSON *root)
{
	t_all_rooms	*rooms_container;
	const cJSON	*rooms_json;

	rooms_container = (t_all_rooms *)calloc(sizeof(t_all_rooms), 1);
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
		return (NULL);
	}
	return (get_rooms(rooms_json, rooms_container));
}
