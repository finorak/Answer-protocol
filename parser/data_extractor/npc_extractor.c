/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_extractor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 19:37:52 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 15:49:10 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/data_extractor.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static t_npc	*get_attack(
	cJSON *content, const cJSON *npc_json, t_npc *npc)
{
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "attack");
	if (!cJSON_IsNumber(content))
		return (free(npc), NULL);
	npc->attack = content->valueint;
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "quest_id");
	if (!cJSON_IsString(content) || !content->valuestring)
		return (free(npc), NULL);
	strncpy(npc->quest_id, content->valuestring, MAX_ID_LEN);
	return (npc);
}

// TODO: separate this function to fit the 25 lines.
t_npc	*extract_npc_from_key(
	const char *key, const cJSON *npc_json, t_npc *npc)
{
	cJSON	*content;

	if (!npc_json || !npc)
		return (free(npc), NULL);
	strncpy(npc->id, key, MAX_ID_LEN);
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "name");
	if (!cJSON_IsString(content) && !content->valuestring)
		return (free(npc), NULL);
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "description");
	if (!cJSON_IsString(content) && !content->valuestring)
		return (free(npc), NULL);
	strncpy(npc->description, content->valuestring, MAX_DESCRIPTION_LEN);
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "dialogues");
	if (!cJSON_IsArray(content))
		return (free(npc), NULL);
	if (!traverse_npc_array(content, npc))
		return (free(npc), NULL);
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "hp");
	if (!cJSON_IsNumber(content))
		return (free(npc), NULL);
	npc->hp = content->valueint;
	return (get_attack(content, npc_json, npc));
}

static t_all_npcs	*get_npcs(const cJSON *npc_json, t_all_npcs *npc_container)
{
	if (!npc_json)
		return (NULL);
	if (!npc_container)
		return (NULL);
	npc_container->len = 0;
	if (!traverse_npc_object(npc_json, npc_container))
		return (NULL);
	return (npc_container);
}

t_all_npcs	*extract_npcs(const cJSON *root)
{
	t_all_npcs	*npc_container;
	const cJSON	*items_json;

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
