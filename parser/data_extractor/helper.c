/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 14:54:13 by finorako          #+#    #+#             */
/*   Updated: 2026/09/30 19:29:46 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world.h"
#include "../../includes/parser.h"
#include "../../includes/cJSON.h"
#include <string.h>

bool	traverse_room_array(
	cJSON *array, t_room *room, char *element_to_extract)
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

	if (!world_json)
		return (false);
	element = world_json->child;
	while (element)
	{
		key = element->string;
		room = (t_room *)malloc(sizeof(t_room));
		if (!room)
		{
			free_rooms(rooms_container, rooms_container->len);
			return (false);
		}
		rooms_container->rooms[rooms_container->len++] = extract_room_from_key(
				key, element, room);
		element = element->next;
	}
	return (true);
}

bool	traverse_item_object(cJSON *item_json, t_all_items *item_container)
{
	t_item	*item;
	cJSON	*element;
	char	*key;

	if (!item_json)
		return (false);
	element = item_json->child;
	while (element)
	{
		key = element->string;
		item = (t_item *)malloc(sizeof(t_item));
		if (!item)
		{
			free_items(item_container, item_container->len);
			return (NULL);
		}
		item_container->items[item_container->len] = extract_item_from_key(
				key, element, item);
		item_container->len += 1;
		element = element->next;
	}
	return (true);
}
