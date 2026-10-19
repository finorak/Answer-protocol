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
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_mission	*extract_mission_from_key(const char *key, const cJSON *npc_json,
				t_mission *mission)
{
	cJSON	*content;

	if (!npc_json || !mission)
		return (NULL);
	strncpy(mission->id, key, MAX_ID_LEN);
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "type");
	if (!is_string(content) || !content->valuestring)
		return (free(mission), NULL);
	strncpy(mission->type, content->valuestring, MAX_ID_LEN);
	content = cJSON_GetObjectItemCaseSensitive(npc_json, "goal");
	if (!is_string(content) || !content->valuestring)
		return (free(mission), NULL);
	strncpy(mission->goal_id, content->valuestring, MAX_ID_LEN);
	return (mission);
}

bool	traverse_mission_object(
	const cJSON *mission_json, t_all_missions *container)
{
	t_mission	*mission;
	cJSON		*element;

	if (!container || !mission_json)
		return (false);
	element = mission_json->child;
	while (element)
	{
		if (!is_object(element))
			return (custom_free(container,
					container->len, TYPE_MISSION), false);
		mission = (t_mission *)calloc(1, sizeof(t_mission));
		container->missions[container->len] = extract_mission_from_key(
				element->string, element, mission);
		if (!container->missions[container->len])
		{
			custom_free(container,
				container->len, TYPE_MISSION);
			return (false);
		}
		container->len += 1;
		element = element->next;
	}
	return (true);
}

static t_all_missions	*get_missions(
	const cJSON *mission_json, t_all_missions *mission_container)
{
	if (!mission_json || !mission_container)
		return (NULL);
	mission_container->len = 0;
	if (!traverse_mission_object(mission_json, mission_container))
		return (NULL);
	return (mission_container);
}

t_all_missions	*extract_missions(const cJSON *root, t_world *data)
{
	t_all_missions	*mission_container;
	t_all_missions	*tmp;
	const cJSON		*mission_json;

	if (!root || !data || !data->extract)
		return (NULL);
	mission_container = (t_all_missions *)calloc(1, sizeof(t_all_missions));
	if (!mission_container)
	{
		data->extract = false;
		return (NULL);
	}
	mission_json = cJSON_GetObjectItemCaseSensitive(root, MISSION_KEY);
	if (!is_object(mission_json))
		return (free(mission_container), NULL);
	tmp = get_missions(mission_json, mission_container);
	data->extract = (bool)tmp;
	return (tmp);
}
