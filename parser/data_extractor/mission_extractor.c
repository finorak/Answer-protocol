/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mission_extractor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 07:56:12 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 15:48:20 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/data_extractor.h"
#include <stdlib.h>
#include <string.h>

t_mission	*extract_mission_from_key(const char *key, const cJSON *npc_json,
				t_mission *mission)
{
	cJSON	*content;

	if (!npc_json)
		return (NULL);
	if (!mission)
		return (NULL);
	strncpy(mission->id, key, MAX_ID_LEN);
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "type");
	if (!cJSON_IsString(content) || !content->valuestring)
		return (NULL);
	strncpy(mission->type, content->valuestring, MAX_ID_LEN);
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "goal");
	if (!cJSON_IsString(content) || !content->valuestring)
		return (NULL);
	strncpy(mission->goal_id, content->valuestring, MAX_ID_LEN);
	return (mission);
}

bool	traverse_mission_object(
	const cJSON *mission_json, t_all_missions *mission_container)
{
	t_mission	*mission;
	cJSON		*element;
	char		*key;

	if (!mission_json)
		return (false);
	if (!mission_container)
		return (false);
	element = mission_json->child;
	while (element)
	{
		key = element->string;
		mission = (t_mission *)calloc(sizeof(t_mission), 1);
		mission_container->missions[
			mission_container->len] = extract_mission_from_key(
				key, element, mission
				);
		if (!mission_container->missions[mission_container->len])
			return (
				free_missions(mission_container,
					mission_container->len), false);
		mission_container->len += 1;
		element = element->next;
	}
	return (true);
}

static t_all_missions	*get_missions(
	const cJSON *mission_json, t_all_missions *mission_container)
{
	if (!mission_json)
		return (NULL);
	if (!mission_container)
		return (NULL);
	mission_container->len = 0;
	if (!traverse_mission_object(mission_json, mission_container))
		return (NULL);
	return (mission_container);
}

t_all_missions	*extract_missions(const cJSON *root)
{
	t_all_missions	*mission_container;
	const cJSON		*mission_json;

	if (!root)
		return (NULL);
	mission_container = (t_all_missions *)calloc(sizeof(t_all_missions), 1);
	if (!mission_container)
		return (NULL);
	mission_json = cJSON_GetObjectItemCaseSensitive(root, MISSION_KEY);
	if (!mission_json)
	{
		free(mission_container);
		return (NULL);
	}
	return (get_missions(mission_json, mission_container));
}
