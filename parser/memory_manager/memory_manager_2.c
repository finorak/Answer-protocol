/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 14:53:10 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 14:53:19 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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
