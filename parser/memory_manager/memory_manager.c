/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 14:25:05 by finorako          #+#    #+#             */
/*   Updated: 2026/10/21 19:07:46 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../../includes/parser.h"

// We regroup the release into a singular function
// so that we can just add another datatype without
// worrying about norminette.
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
		release_data(data, data_type, index++);
	if (data_type != TYPE_STRING_TABLE)
		free(data);
}

void	free_data(t_world *data, char *buffer, bool free_all_data)
{
	if (buffer)
		free(buffer);
	if (!data || !free_all_data)
		return ;
	custom_free(data->rooms, data->rooms->len, TYPE_ROOM);
	custom_free(data->items, data->items->len, TYPE_ITEM);
	custom_free(data->npcs, data->npcs->len, TYPE_NPC);
	custom_free(data->quests, data->quests->len, TYPE_QUEST);
	custom_free(data->missions, data->missions->len, TYPE_MISSION);
	custom_free(data->dialogues, data->dialogues->len, TYPE_DIALOG);
	custom_free(data->groups, data->groups->len, TYPE_GROUP);
	if (data->players)
		free(data->players);
	free(data);
}

void	free_world_fail(t_world *data, char *buffer)
{
	free(buffer);
	free(data);
}
