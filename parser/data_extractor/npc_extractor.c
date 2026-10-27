/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_extractor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 19:37:52 by finorako          #+#    #+#             */
/*   Updated: 2026/10/27 06:07:01 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/data_extractor.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static t_npc	*get_attack(
	cJSON *content, const cJSON *npc_json, t_npc *npc)
{
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "attack");
	if (!content || !cJSON_IsNumber(content) || content->valueint < -1)
		return (free(npc), NULL);
	npc->attack = content->valueint;
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "quest_id");
	if (!content || !cJSON_IsString(content) || !content->valuestring)
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
	if (!content || !cJSON_IsString(content) || !content->valuestring)
		return (free(npc), NULL);
	strncpy(npc->name, content->valuestring, MAX_NAME_LEN);
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "description");
	if (!content || !cJSON_IsString(content) || !content->valuestring)
		return (free(npc), NULL);
	strncpy(npc->description, content->valuestring, MAX_DESCRIPTION_LEN);
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "dialogues");
	if (!content || !cJSON_IsArray(content))
		return (free(npc), NULL);
	if (!content || !traverse_npc_array(content, npc))
		return (free(npc), NULL);
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "hp");
	if (!content || !cJSON_IsNumber(content) || content->valueint < -1)
		return (free(npc), NULL);
	npc->hp = content->valueint;
	return (get_attack(content, npc_json, npc));
}

static t_all_npcs	*get_npcs(const cJSON *npc_json, t_all_npcs *npc_container)
{
	if (!npc_json || !npc_container)
		return (NULL);
	npc_container->len = 0;
	if (!traverse_npc_object(npc_json, npc_container))
		return (NULL);
	return (npc_container);
}

t_all_npcs	*extract_npcs(const cJSON *root, t_world *data)
{
	const cJSON	*items_json;
	t_all_npcs	*npc_container;
	t_all_npcs	*tmp;

	if (!root || !data || !data->extract)
		return (NULL);
	npc_container = (t_all_npcs *)calloc(1, sizeof(t_all_npcs));
	if (!npc_container)
	{
		data->extract = false;
		return (NULL);
	}
	items_json = cJSON_GetObjectItemCaseSensitive(root, NPC_KEY);
	if (!items_json)
	{
		data->extract = false;
		fprintf(stderr, "'%s' key not found or is not an object\n", NPC_KEY);
		return (free(npc_container), NULL);
	}
	tmp = get_npcs(items_json, npc_container);
	data->extract = (bool)tmp;
	return (tmp);
}
