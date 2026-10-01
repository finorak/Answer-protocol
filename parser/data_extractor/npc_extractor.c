/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_extractor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 19:37:52 by finorako          #+#    #+#             */
/*   Updated: 2026/09/30 20:00:41 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/data_extractor.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// TODO: separate this function to fit the 25 lines.
t_npc	*extract_npc_from_key(const char *key, cJSON *npc_json, t_npc *npc)
{
	t_json_content	content;

	if (!npc_json || !npc)
		return (false);
	strncpy(npc->id, key, BUFFER_SIZE);
	content.name = cJSON_GetObjectItemCaseSensitive(npc_json, "name");
	if (!cJSON_IsString(content.name) && !content.name->valuestring)
		return (NULL);
	content.desc = cJSON_GetObjectItemCaseSensitive(npc_json, "description");
	if (!cJSON_IsString(content.desc) && !content.desc->valuestring)
		return (NULL);
	strncpy(npc->description, content.desc->valuestring, BUFFER_SIZE);
	content.dialogues = cJSON_GetObjectItemCaseSensitive(npc_json, "dialogues");
	if (!cJSON_IsArray(content.dialogues))
		return (NULL);
	if (!traverse_npc_array(content.dialogues, npc))
		return (NULL);
	content.hp = cJSON_GetObjectItemCaseSensitive(npc_json, "hp");
	if (!cJSON_IsNumber(content.hp))
		return (NULL);
	npc->hp = content.hp->valueint;
	content.attack = cJSON_GetObjectItemCaseSensitive(npc_json, "attack");
	if (!cJSON_IsNumber(content.attack))
		return (NULL);
	npc->attack = content.attack->valueint;
	return (npc);
	content.quest_id = cJSON_GetObjectItemCaseSensitive(npc_json, "quest_id");
	if (!cJSON_IsString(content.quest_id) && !content.quest_id->valuestring)
		return (NULL);
	strncpy(npc->quest_id, content.quest_id->valuestring, BUFFER_SIZE);
}

static t_all_npcs	*get_npcs(cJSON *npc_json, t_all_npcs *npc_container)
{
	if (!npc_json)
		return (NULL);
	if (!npc_container)
		return (NULL);
	if (!traverse_npc_object(npc_json, npc_container))
		return (NULL);
	return (npc_container);
}

t_all_npcs	*extract_npcs(cJSON *root)
{
	t_all_npcs	*npc_container;
	cJSON		*items_json;

	if (!root)
		return (NULL);
	npc_container = (t_all_npcs *)calloc(sizeof(t_all_npcs), 1);
	if (!npc_container)
		return (NULL);
	items_json = cJSON_GetObjectItemCaseSensitive(root, NPC_KEY);
	if (!items_json)
	{
		fprintf(stderr, "'%s' key not found or is not an object\n", NPC_KEY);
		free(npc_container);
		return (NULL);
	}
	return (get_npcs(items_json, npc_container));
}
