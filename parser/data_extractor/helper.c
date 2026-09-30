/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 14:54:13 by finorako          #+#    #+#             */
/*   Updated: 2026/09/30 16:51:19 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world.h"
#include "../../includes/parser.h"
#include "../../includes/cJSON.h"
#include <string.h>

bool	traverse_array(cJSON *array, t_room *room, char *element_to_extract)
{
	cJSON	*element;
	int		index;

	if (!array)
		return (NULL);
	index = 0;
	element = array->child;
	while (element)
	{
		if (!cJSON_IsString(element) && !element->valuestring)
			return (NULL);
		if (strcmp(element_to_extract, "exits") == 0)
			strncpy(room->exits.ids[index], element->valuestring, BUFFER_SIZE);
		else if (strcmp(element_to_extract, "npcs") == 0)
			strncpy(room->npcs.ids[index], element->valuestring, BUFFER_SIZE);
		else if (strcmp(element_to_extract, "items") == 0)
			strncpy(room->items.ids[index], element->valuestring, BUFFER_SIZE);
		element = element->next;
		index++;
	}
	room->exits.len = index;
	return (true);
}

bool	traverse_room_object(cJSON *world_json, t_all_rooms *rooms_container)
{
	t_room	*room;
	cJSON	*element;
	char	*key;
	int		index;

	if (!world_json)
		return (false);
	element = world_json->child;
	index = 0;
	while (element)
	{
		key = element->string;
		room = (t_room *)malloc(sizeof(t_room));
		if (!room)
			return (NULL);
		rooms_container->rooms[index] = extract_room_from_key(
				key, element, room);
		if (!rooms_container->rooms[index])
			return (false);
		element = element->next;
		index += 1;
	}
	rooms_container->len = index;
	return (true);
}
