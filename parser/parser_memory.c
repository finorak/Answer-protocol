/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 14:25:05 by finorako          #+#    #+#             */
/*   Updated: 2026/10/01 09:01:51 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../includes/parser.h"

void	free_rooms(t_all_rooms *rooms, int size)
{
	int	index;

	if (!rooms)
		return ;
	index = 0;
	while (index < size)
	{
		free(rooms->rooms[index]);
		index += 1;
	}
	free(rooms);
}

void	free_items(t_all_items *items, int size)
{
	int	index;

	if (!items)
		return ;
	index = 0;
	while (index < size)
	{
		free(items->items[index]);
		index ++;
	}
	free(items);
}

void	free_npcs(t_all_npcs *items, int size)
{
	int	index;

	if (!items)
		return ;
	index = 0;
	while (index < size)
	{
		free(items->npcs[index]);
		index ++;
	}
	free(items);
}

void	free_quests(t_all_quests *items, int size)
{
	int	index;

	if (!items)
		return ;
	index = 0;
	while (index < size)
	{
		free(items->quests[index]);
		index ++;
	}
	free(items);
}

void	free_missions(t_all_missions *items, int size)
{
	int	index;

	if (!items)
		return ;
	index = 0;
	while (index < size)
	{
		free(items->missions[index]);
		index ++;
	}
	free(items);
}

void	free_dialogues(t_all_dialogues *items, int size)
{
	int	index;

	if (!items)
		return ;
	index = 0;
	while (index < size)
	{
		free(items->dialogues[index]);
		index += 1;
	}
	free(items);
}

void	free_groups(t_all_groups *groups, int size)
{
	int	index;

	if (!groups)
		return ;
	index = 0;
	while (index < size)
	{
		printf("%s\n", groups->groups[index]->name);
		free(groups->groups[index]);
		index += 1;
	}
	free(groups);
}

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
