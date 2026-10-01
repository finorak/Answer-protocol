/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_part_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 14:54:13 by finorako          #+#    #+#             */
/*   Updated: 2026/10/01 06:31:51 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world.h"
#include "../../includes/parser.h"
#include "../../includes/cJSON.h"

bool	traverse_room_array(
	cJSON *array, t_room *room, char *element_to_extract)
{
	cJSON	*element;
	int		index;

	if (!array)
		return (false);
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

// TODO: Memory managment
bool	traverse_npc_array(cJSON *array, t_npc *npc)
{
	cJSON	*element;
	int		index;

	if (!array)
		return (false);
	index = 0;
	element = array->child;
	while (element)
	{
		if (!cJSON_IsString(element))
			return (NULL);
		strncpy(npc->dialogues.ids[index], element->valuestring, BUFFER_SIZE);
		index += 1;
		element = element->next;
	}
	npc->dialogues.len = index;
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
	rooms_container->len = 0;
	while (element)
	{
		key = element->string;
		room = (t_room *)calloc(sizeof(t_room), 1);
		rooms_container->rooms[rooms_container->len] = extract_room_from_key(
				key, element, room);
		if (!rooms_container->rooms[rooms_container->len])
		{
			free_rooms(rooms_container, rooms_container->len);
			return (false);
		}
		rooms_container->len += 1;
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
		item = (t_item *)calloc(sizeof(t_item), 1);
		item_container->items[item_container->len] = extract_item_from_key(
				key, element, item);
		if (!item_container->items[item_container->len])
		{
			free_items(item_container, item_container->len);
			return (NULL);
		}
		item_container->len += 1;
		element = element->next;
	}
	return (true);
}

// TODO: ADDING MEMORY MANAGEMENT.
bool	traverse_npc_object(cJSON *npc_json, t_all_npcs *npc_container)
{
	t_npc	*npc;
	cJSON	*element;
	char	*key;

	if (!npc_json)
		return (false);
	element = npc_json->child;
	npc_container->len = 0;
	while (element)
	{
		key = element->string;
		npc = (t_npc *)calloc(sizeof(t_npc), 1);
		npc_container->npcs[npc_container->len] = extract_npc_from_key(
				key, element, npc
				);
		if (!npc_container->npcs[npc_container->len])
			return (NULL);
		npc_container->len += 1;
		element = element->next;
	}
	return (true);
}
