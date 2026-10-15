/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:27:44 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/15 10:27:45 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

t_item	*get_item_by_id(char *id, t_world *world)
{
	int	i;

	i = 0;
	while (i < world->items.len)
	{
		if (world->items.items[i].id == id)
			return (&(world->items.items[i]));
		i++;
	}
	return (NULL);
}

t_npc	*get_npc_by_id(char *id, t_world *world)
{
	int	i;

	i = 0;
	while (i < world->npcs.len)
	{
		if (world->npcs.npcs[i].id == id)
			return (&(world->npcs.npcs[i]));
		i++;
	}
	return (NULL);
}

t_quest	*get_quest_by_id(char *id, t_world *world)
{
	int	i;

	i = 0;
	while (i < world->quests.len)
	{
		if (world->quests.quests[i].id == id)
			return (&(world->quests.quests[i]));
		i++;
	}
	return (NULL);
}

t_mission	*get_mission_by_id(char *id, t_world *world)
{
	int	i;

	i = 0;
	while (i < world->missions.len)
	{
		if (world->missions.missions[i].id == id)
			return (&(world->missions.missions[i]));
		i++;
	}
	return (NULL);
}

t_dialogue	*get_dialogue_by_id(char *id, t_world *world)
{
	int	i;

	i = 0;
	while (i < world->dialogues.len)
	{
		if (world->dialogues.dialogues[i].id == id)
			return (&(world->dialogues.dialogues[i]));
		i++;
	}
	return (NULL);
}
