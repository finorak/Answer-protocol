/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quest_extractor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 23:24:15 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 15:47:41 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/data_extractor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static t_quest	*get_owner(
	cJSON *content, const cJSON *quest_json, t_quest *quest)
{
	strncpy(quest->reward_id, content->valuestring, MAX_ID_LEN);
	content = cJSON_GetObjectItemCaseSensitive(
			quest_json, "npc_owner");
	if (!cJSON_IsString(content) || !content->valuestring)
		return (free(quest), NULL);
	strncpy(quest->npc_owner_id, content->valuestring, MAX_ID_LEN);
	return (quest);
}

t_quest	*extract_quest_from_key(
			const char *key, const cJSON *quest_json, t_quest *quest)
{
	cJSON	*content;

	if (!quest_json || !quest)
		return (free(quest), NULL);
	content = cJSON_GetObjectItemCaseSensitive(quest_json, "name");
	if (!cJSON_IsString(content) || !content->valuestring)
		return (free(quest), NULL);
	strncpy(quest->name, content->valuestring, MAX_NAME_LEN);
	strncpy(quest->id, key, MAX_ID_LEN);
	content = cJSON_GetObjectItemCaseSensitive(quest_json, "description");
	if (!cJSON_IsString(content) || !content->valuestring)
		return (free(quest), NULL);
	content = cJSON_GetObjectItemCaseSensitive(quest_json, "missions");
	if (!cJSON_IsArray(content))
		return (free(quest), NULL);
	if (!traverse_quest_array(content, quest))
		return (free(quest), NULL);
	content = cJSON_GetObjectItemCaseSensitive(quest_json, "reward");
	if (!cJSON_IsString(content) || !content->valuestring)
		return (free(quest), NULL);
	return (get_owner(content, quest_json, quest));
}

static t_all_quests	*get_quests(
	const cJSON *quest_json, t_all_quests *quest_container)
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

t_all_quests	*extract_quests(const cJSON *root)
{
	t_all_quests	*quest_container;
	const cJSON		*quest_json;

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
