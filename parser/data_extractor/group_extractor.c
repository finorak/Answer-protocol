/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_extractor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 08:47:09 by finorako          #+#    #+#             */
/*   Updated: 2026/10/18 13:42:54 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/data_extractor.h"
#include "../../includes/parser.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

t_group	*extract_group_from_key(
	const char *key, cJSON *group_json, t_group *group)
{
	if (!group_json || !group)
		return (NULL);
	strncpy(group->name, group_json->valuestring, MAX_NAME_LEN);
	(void)key;
	return (group);
}

bool	traverse_group_object(
	const cJSON *group_json, t_all_groups *container)
{
	t_group	*group;
	cJSON	*element;
	char	*key;

	if (!group_json || !container)
		return (false);
	element = group_json->child;
	while (element)
	{
		if (!cJSON_IsString(element))
			return (custom_free(container, container->len, TYPE_GROUP), false);
		key = element->string;
		group = (t_group *)calloc(1, sizeof(t_group));
		container->groups[container->len] = extract_group_from_key(
				key, element, group
				);
		if (!container->groups[container->len])
			return (custom_free(container, container->len, TYPE_GROUP), false);
		container->len += 1;
		element = element->next;
	}
	return (true);
}

static t_all_groups	*get_dialogue(
	const cJSON *group_json, t_all_groups *group_container)
{
	if (!group_json || !group_container)
		return (NULL);
	group_container->len = 0;
	if (!traverse_group_object(group_json, group_container))
		return (NULL);
	return (group_container);
}

t_all_groups	*extract_groups(const cJSON *root, t_world *data)
{
	t_all_groups	*group_container;
	t_all_groups	*tmp;
	const cJSON		*group_json;

	if (!root || !data || !data->extract)
		return (NULL);
	group_container = (t_all_groups *)calloc(1, sizeof(t_all_groups));
	if (!group_container)
		return (NULL);
	group_json = cJSON_GetObjectItemCaseSensitive(root, GROUP_KEY);
	if (!is_object(group_json))
		return (free(group_container), NULL);
	tmp = get_dialogue(group_json, group_container);
	data->extract = (bool)tmp;
	return (tmp);
}
