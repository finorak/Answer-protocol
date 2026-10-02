/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_extractor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 18:21:16 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 15:49:43 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/data_extractor.h"
#include <stdlib.h>

t_item	*extract_item_from_key(
	const char *key, const cJSON *item_json, t_item *item)
{
	t_json_content	content;

	if (!item_json || !item)
		return (NULL);
	strncpy(item->id, key, MAX_ID_LEN);
	content.name = cJSON_GetObjectItemCaseSensitive(item_json, "name");
	if (!cJSON_IsString(content.name) && !content.name)
		return (NULL);
	strncpy(item->name, content.name->valuestring, MAX_NAME_LEN);
	content.desc = cJSON_GetObjectItemCaseSensitive(item_json, "description");
	if (!cJSON_IsString(content.desc) && !content.desc->valuestring)
		return (NULL);
	strncpy(item->description, content.desc->valuestring, MAX_DESCRIPTION_LEN);
	content.obtainable = cJSON_GetObjectItemCaseSensitive(
			item_json, "obtainable");
	if (!cJSON_IsNumber(content.obtainable))
		return (false);
	item->obtainable = content.obtainable->valueint;
	content.heal = cJSON_GetObjectItemCaseSensitive(item_json, "heal");
	if (!cJSON_IsNumber(content.heal))
		return (NULL);
	return (item);
}

static t_all_items	*get_items(
	const cJSON *items_json, t_all_items *items_container)
{
	if (!items_json)
		return (NULL);
	if (!items_container)
		return (NULL);
	items_container->len = 0;
	if (!traverse_item_object(items_json, items_container))
		return (NULL);
	return (items_container);
}

t_all_items	*extract_items(const cJSON *root)
{
	t_all_items	*items_container;
	const cJSON	*items_json;

	if (!root)
		return (NULL);
	items_container = (t_all_items *)calloc(sizeof(t_all_items), 1);
	if (!items_container)
		return (NULL);
	items_json = cJSON_GetObjectItemCaseSensitive(root, ITEMS_KEY);
	if (!items_json)
	{
		fprintf(stderr, "'%s' key not found or is not an object\n", ITEMS_KEY);
		free(items_container);
		return (NULL);
	}
	return (get_items(items_json, items_container));
}
