/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_extractor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 08:47:09 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 15:44:32 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/data_extractor.h"
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
	const cJSON *group_json, t_all_groups *group_container)
{
	t_group	*group;
	cJSON	*element;
	char	*key;

	if (!group_json || !group_container)
		return (false);
	element = group_json->child;
	while (element)
	{
		key = element->string;
		group = (t_group *)calloc(sizeof(t_group), 1);
		group_container->groups[group_container->len] = extract_group_from_key(
				key, element, group
				);
		if (!group_container->groups[group_container->len])
			return (false);
		group_container->len += 1;
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

t_all_groups	*extract_groups(const cJSON *root)
{
	t_all_groups	*group_container;
	const cJSON		*group_json;

	if (!root)
		return (NULL);
	group_container = (t_all_groups *)calloc(sizeof(t_all_groups), 1);
	if (!group_container)
		return (NULL);
	group_json = cJSON_GetObjectItemCaseSensitive(root, "groups");
	if (!group_json)
	{
		free(group_container);
		return (NULL);
	}
	return (get_dialogue(group_json, group_container));
}
