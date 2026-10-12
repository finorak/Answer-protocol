/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 14:25:05 by finorako          #+#    #+#             */
/*   Updated: 2026/10/12 10:59:40 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/parser.h"

static void	release_data(void *data, t_data_type data_type, int index)
{
	if (data_type == TYPE_STRING_TABLE)
		free(((char **)data)[index]);
	else if (data_type == TYPE_GROUP)
		free(((t_all_groups *)data)->groups[index]);
	else if (data_type == TYPE_DIALOG)
		free(((t_all_dialogues *)data)->dialogues[index]);
	else if (data_type == TYPE_ITEM)
		free(((t_all_items *)data)->items[index]);
	else if (data_type == TYPE_MISSION)
		free(((t_all_missions *)data)->missions[index]);
	else if (data_type == TYPE_NPC)
		free(((t_all_npcs *)data)->npcs[index]);
	else if (data_type == TYPE_QUEST)
		free(((t_all_quests *)data)->quests[index]);
	else if (data_type == TYPE_ROOM)
		free(((t_all_rooms *)data)->rooms[index]);
}

void	custom_free(void *data, int size, t_data_type data_type)
{
	int	index;

	if (!data)
		return ;
	index = 0;
	while (index < size)
	{
		release_data(data, data_type, index);
		index ++;
	}
	free(data);
}

void	free_data(t_data *data, char *buffer)
{
	if (buffer)
		free(buffer);
	if (!data)
		return ;
	custom_free(data->rooms, data->rooms->len, TYPE_ROOM);
	custom_free(data->items, data->items->len, TYPE_ITEM);
	custom_free(data->npcs, data->npcs->len, TYPE_NPC);
	custom_free(data->quests, data->quests->len, TYPE_QUEST);
	custom_free(data->missions, data->missions->len, TYPE_MISSION);
	custom_free(data->dialogues, data->dialogues->len, TYPE_DIALOG);
	custom_free(data->groups, data->groups->len, TYPE_GROUP);
	if (data)
		free(data);
}
