/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dialogue_extractor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 08:23:10 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 15:44:08 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/data_extractor.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

t_dialogue	*extract_dialogues_from_key(
				const char *key, cJSON *dialogue_json, t_dialogue *dialogue)
{
	if (!dialogue_json)
		return (NULL);
	if (!dialogue)
		return (NULL);
	strncpy(dialogue->id, key, MAX_ID_LEN);
	strncpy(
		dialogue->content, dialogue_json->valuestring,
		MAX_DIALOGUE_CONTENT_LEN);
	return (dialogue);
}

bool	traverse_dialogue_object(
	const cJSON *dialogue_json, t_all_dialogues *container)
{
	t_dialogue	*dialogue;
	cJSON		*element;
	char		*key;

	if (!dialogue_json)
		return (NULL);
	if (!container)
		return (NULL);
	element = dialogue_json->child;
	while (element)
	{
		key = element->string;
		dialogue = (t_dialogue *)calloc(1, sizeof(t_dialogue));
		container->dialogues[
			container->len] = extract_dialogues_from_key(
				key, element, dialogue
				);
		if (!container->dialogues[container->len])
			return (custom_free(container, container->len, TYPE_DIALOG), NULL);
		container->len += 1;
		element = element->next;
	}
	return (true);
}

static t_all_dialogues	*get_dialogue(
	const cJSON *dialogue_json, t_all_dialogues *dialogue_container)
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

// Extracting dialogues from the root json.
t_all_dialogues	*extract_dialogues(const cJSON *root, t_data *data)
{
	t_all_dialogues	*dialogue_container;
	t_all_dialogues	*tmp;
	const cJSON		*dialogue_json;

	if (!root || !data || !data->extract)
		return (NULL);
	dialogue_container = (t_all_dialogues *)calloc(1, sizeof(t_all_dialogues));
	if (!dialogue_container)
	{
		data->extract = false;
		return (NULL);
	}
	dialogue_json = cJSON_GetObjectItemCaseSensitive(root, "dialogues");
	if (!dialogue_json)
	{
		data->extract = false;
		free(dialogue_container);
		return (NULL);
	}
	tmp = get_dialogue(dialogue_json, dialogue_container);
	if (!tmp)
		data->extract = false;
	return (tmp);
}
