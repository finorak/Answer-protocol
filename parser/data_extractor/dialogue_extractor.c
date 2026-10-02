/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dialogue_extractor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 08:23:10 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 10:57:09 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/data_extractor.h"
#include <stdlib.h>

t_dialogue	*extract_dialogues_from_key(
				const char *key, cJSON *dialogue_json, t_dialogue *dialogue)
{
	if (!dialogue_json)
		return (NULL);
	if (!dialogue)
		return (NULL);
	strncpy(dialogue->id, key, BUFFER_SIZE);
	strncpy(dialogue->content, dialogue_json->valuestring, BUFFER_SIZE);
	return (dialogue);
}

bool	traverse_dialogue_object(
	cJSON *dialogue_json, t_all_dialogues *dialogue_container)
{
	t_dialogue	*dialogue;
	cJSON		*element;
	char		*key;
	int			index;

	if (!dialogue_json)
		return (NULL);
	if (!dialogue_container)
		return (NULL);
	index = 0;
	element = dialogue_json->child;
	while (element)
	{
		key = element->string;
		dialogue = (t_dialogue *)calloc(sizeof(t_dialogue), 1);
		dialogue_container->dialogues[index] = extract_dialogues_from_key(
				key, element, dialogue
				);
		if (!dialogue_container->dialogues[index])
			return (NULL);
		index += 1;
		element = element->next;
	}
	dialogue_container->len = index;
	return (true);
}

static t_all_dialogues	*get_dialogue(
	cJSON *dialogue_json, t_all_dialogues *dialogue_container)
{
	if (!dialogue_json)
		return (NULL);
	if (!dialogue_container)
		return (NULL);
	dialogue_container->len = 0;
	if (!traverse_dialogue_object(dialogue_json, dialogue_container))
		return (NULL);
	return (dialogue_container);
}

t_all_dialogues	*extract_dialogues(const cJSON *root)
{
	t_all_dialogues	*dialogue_container;
	cJSON			*dialogue_json;

	if (!root)
		return (NULL);
	dialogue_container = (t_all_dialogues *)calloc(sizeof(t_all_dialogues), 1);
	if (!dialogue_container)
		return (NULL);
	dialogue_json = cJSON_GetObjectItemCaseSensitive(root, "dialogues");
	if (!dialogue_json)
	{
		free(dialogue_container);
		return (NULL);
	}
	return (get_dialogue(dialogue_json, dialogue_container));
}
