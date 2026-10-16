/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_part_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 14:54:13 by finorako          #+#    #+#             */
/*   Updated: 2026/10/11 16:34:18 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world.h"
#include "../../includes/parser.h"
#include "../../includes/cJSON.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool	traverse_room_array(
	const cJSON *array, t_room *room, const char *element_to_extract)
{
	cJSON	*element;
	char	*value;
	int		index;

	if (!array)
		return (false);
	index = 0;
	element = array->child;
	while (element)
	{
		if (!cJSON_IsString(element) || !element->valuestring)
			return (NULL);
		value = element->valuestring;
		if (strcmp(element_to_extract, "exits") == 0)
			strncpy(room->exits.ids[index], value, MAX_ID_LEN);
		else if (strcmp(element_to_extract, "npcs") == 0)
			strncpy(room->npcs.ids[index], value, MAX_ID_LEN);
		else if (strcmp(element_to_extract, "items") == 0)
			strncpy(room->items.ids[index], value, MAX_ID_LEN);
		element = element->next;
		index++;
	}
	return (true);
}

// TODO: Memory managment
bool	traverse_npc_array(const cJSON *array, t_npc *npc)
{
	cJSON	*element;

	if (!array)
		return (false);
	element = array->child;
	npc->dialogues.len = 0;
	while (element)
	{
		if (!cJSON_IsString(element))
			return (NULL);
		strncpy(
			npc->dialogues.ids[npc->dialogues.len],
			element->valuestring, MAX_ID_LEN);
		npc->dialogues.len += 1;
		element = element->next;
	}
	return (true);
}

bool	traverse_room_object(
	const cJSON *world_json, t_all_rooms *container)
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
		room = (t_room *)calloc(1, sizeof(t_room));
		container->rooms[container->len] = extract_room_from_key(
				key, element, room);
		if (!container->rooms[container->len])
		{
			custom_free(container, container->len, TYPE_ROOM);
			return (false);
		}
		container->rooms[container->len]->exits.len = 4;
		container->len += 1;
		element = element->next;
	}
	return (true);
}

bool	traverse_item_object(
	const cJSON *item_json, t_all_items *container)
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
		item = (t_item *)calloc(1, sizeof(t_item));
		container->items[container->len] = extract_item_from_key(
				key, element, item);
		if (!container->items[container->len])
		{
			custom_free(container, container->len, TYPE_ITEM);
			return (false);
		}
		container->len += 1;
		element = element->next;
	}
	return (true);
}

// TODO: ADDING MEMORY MANAGEMENT.
bool	traverse_npc_object(
	const cJSON *npc_json, t_all_npcs *container)
{
	t_npc	*npc;
	cJSON	*element;
	char	*key;

	if (!npc_json)
		return (false);
	element = npc_json->child;
	while (element)
	{
		key = element->string;
		npc = (t_npc *)calloc(1, sizeof(t_npc));
		container->npcs[container->len] = extract_npc_from_key(
				key, element, npc
				);
		if (!container->npcs[container->len])
		{
			custom_free(container, container->len, TYPE_NPC);
			return (false);
		}
		container->len += 1;
		element = element->next;
	}
	return (true);
}
