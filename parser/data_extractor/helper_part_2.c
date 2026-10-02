/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_part_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 06:21:17 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 15:30:41 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world.h"
#include "../../includes/parser.h"
#include "../../includes/cJSON.h"
#include <stdlib.h>

bool	traverse_quest_object(
	const cJSON *world_json, t_all_quests *quest_container)
{
	t_quest	*quest;
	cJSON	*element;
	char	*key;

	if (!world_json)
		return (false);
	if (!quest_container)
		return (false);
	element = world_json->child;
	while (element)
	{
		key = element->string;
		quest = (t_quest *)calloc(sizeof(t_quest), 1);
		quest_container->quests[quest_container->len] = extract_quest_from_key(
				key, element, quest
				);
		if (!quest_container->quests[quest_container->len])
			return (NULL);
		quest_container->len += 1;
		element = element->next;
	}
	return (true);
}

bool	traverse_quest_array(const cJSON *array, t_quest *quest)
{
	cJSON	*element;
	int		index;

	if (!array || !quest)
		return (false);
	index = 0;
	element = array->child;
	while (element)
	{
		if (!cJSON_IsString(element) && !element->valuestring)
			return (false);
		strncpy(quest->missions.ids[index], element->valuestring, BUFFER_SIZE);
		index += 1;
		element = element->next;
	}
	quest->missions.len = index;
	return (true);
}
