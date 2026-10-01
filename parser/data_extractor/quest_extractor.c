/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quest_extractor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 23:24:15 by finorako          #+#    #+#             */
/*   Updated: 2026/10/01 07:56:22 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/data_extractor.h"
#include <string.h>

t_quest	*extract_quest_from_key(
			const char *key, cJSON *quest_json, t_quest *quest)
{
	t_json_content	content;

	if (!quest_json || !quest)
		return (NULL);
	content.name = cJSON_GetObjectItemCaseSensitive(quest_json, "name");
	if (!cJSON_IsString(content.name) && !content.name->valuestring)
		return (NULL);
	strncpy(quest->name, content.name->valuestring, BUFFER_SIZE);
	strncpy(quest->id, key, BUFFER_SIZE);
	content.desc = cJSON_GetObjectItemCaseSensitive(quest_json, "description");
	if (!cJSON_IsString(content.desc) && !content.desc->valuestring)
		return (NULL);
	content.missions = cJSON_GetObjectItemCaseSensitive(quest_json, "missions");
	if (!cJSON_IsArray(content.missions))
		return (NULL);
	if (!traverse_quest_array(content.missions, quest))
		return (NULL);
	content.reward = cJSON_GetObjectItemCaseSensitive(quest_json, "reward");
	if (!cJSON_IsString(content.reward) && !content.reward->valuestring)
		return (NULL);
	strncpy(quest->reward_id, content.reward->valuestring, BUFFER_SIZE);
	content.npc_owner = cJSON_GetObjectItemCaseSensitive(
			quest_json, "npc_owner");
	if (!cJSON_IsString(content.npc_owner) && !content.npc_owner->valuestring)
		return (NULL);
	strncpy(quest->npc_owner_id, content.npc_owner->valuestring, BUFFER_SIZE);
	return (quest);
}

static t_all_quests	*get_quests(
	cJSON *quest_json, t_all_quests *quest_container)
{
	if (!quest_json)
		return (NULL);
	if (!quest_container)
		return (NULL);
	quest_container->len = 0;
	if (!traverse_quest_object(quest_json, quest_container))
		return (NULL);
	return (quest_container);
}

t_all_quests	*extract_quests(cJSON *root)
{
	t_all_quests	*quest_container;
	cJSON			*quest_json;

	if (!root)
		return (NULL);
	quest_container = (t_all_quests *)calloc(sizeof(t_all_quests), 1);
	if (!quest_container)
		return (NULL);
	quest_json = cJSON_GetObjectItemCaseSensitive(root, QUEST_KEY);
	if (!quest_json)
	{
		fprintf(stderr, "'%s' key not found or is not an object\n", QUEST_KEY);
		free(quest_container);
		return (NULL);
	}
	return (get_quests(quest_json, quest_container));
}
