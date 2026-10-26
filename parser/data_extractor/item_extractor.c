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
#include "../../ft_printf/ft_printf.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

t_item	*extract_item_from_key(
	const char *key, const cJSON *item_json, t_item *item)
{
	cJSON	*content;

	if (!item_json || !item)
		return (free(item), NULL);
	strncpy(item->id, key, MAX_ID_LEN);
	content = cJSON_GetObjectItemCaseSensitive(item_json, "name");
	if (!content || !cJSON_IsString(content) || !content->valuestring)
		return (free(item), NULL);
	strncpy(item->name, content->valuestring, MAX_NAME_LEN);
	content = cJSON_GetObjectItemCaseSensitive(item_json, "description");
	if (!content || !cJSON_IsString(content) || !content->valuestring)
		return (free(item), NULL);
	strncpy(item->description, content->valuestring, MAX_DESCRIPTION_LEN);
	content = cJSON_GetObjectItemCaseSensitive(
			item_json, "obtainable");
	if (!content || !cJSON_IsNumber(content))
		return (free(item), NULL);
	item->obtainable = content->valueint;
	content = cJSON_GetObjectItemCaseSensitive(item_json, "heal");
	if (!content || !cJSON_IsNumber(content))
		return (free(item), NULL);
	return (item);
}

static t_all_items	*get_items(
	const cJSON *items_json, t_all_items *items_container)
{
	if (!items_json || !items_container)
		return (NULL);
	items_container->len = 0;
	if (!traverse_item_object(items_json, items_container))
		return (NULL);
	return (items_container);
}

t_all_items	*extract_items(const cJSON *root, t_world *data)
{
	t_all_items	*items_container;
	const cJSON	*items_json;
	t_all_items	*tmp;

	if (!root || !data || !data->extract)
		return (NULL);
	items_container = (t_all_items *)calloc(1, sizeof(t_all_items));
	if (!items_container)
	{
		data->extract = false;
		return (NULL);
	}
	items_json = cJSON_GetObjectItemCaseSensitive(root, ITEMS_KEY);
	if (!items_json)
	{
		fprintf(stderr, "'%s' key not found or is not an object\n", ITEMS_KEY);
		free(items_container);
		return (NULL);
	}
	tmp = get_items(items_json, items_container);
	data->extract = (bool)tmp;
	return (tmp);
}
