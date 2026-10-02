/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 14:25:05 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 14:54:22 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/parser.h"

void	free_data(t_data *data, char *buffer)
{
	if (buffer)
		free(buffer);
	if (data->rooms)
		free_rooms(data->rooms, data->rooms->len);
	if (data->items)
		free_items(data->items, data->items->len);
	if (data->npcs)
		free_npcs(data->npcs, data->npcs->len);
	if (data->quests)
		free_quests(data->quests, data->quests->len);
	if (data->missions)
		free_missions(data->missions, data->missions->len);
	if (data->dialogues)
		free_dialogues(data->dialogues, data->dialogues->len);
	if (data->groups)
		free_groups(data->groups, data->groups->len);
	if (data)
		free(data);
}
