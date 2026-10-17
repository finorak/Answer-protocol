/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_complete_quest.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:33:59 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 20:09:13 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../main_utils.h"

static int	take(char *item_id, t_world *g_world, int client_fd)
{
	if (in(item_id, get_player_by_fd(client_fd, g_world)->items))
		return (1);
	else
		return (0);
}

static int	kill(char *npc_id, t_world *g_world)
{
	if (get_npc_by_id(npc_id, g_world)->hp == 0)
		return (1);
	else
		return (0);
}

static void	util_left(t_world *g_world, t_signal *result)
{
	char	temp[12];

	fill_with_all(result, g_world);
	all_items_left(g_world, temp);
	strcpy(result->messages_0, "EVT STATS items=");
	strcat(result->messages_0, temp);
	strcat(result->messages_0, "\n");
}

static void	complete_quest(t_quest *quest, t_world *g_world, int client_fd)
{
	int			i;
	t_mission	*mission;

	quest->done_missions = 0;
	i = 0;
	while (i < quest->missions.len)
	{
		mission = get_mission_by_id(quest->missions.ids[i], g_world);
		if (!strcmp(mission->type, "take"))
			quest->done_missions += take(mission->goal_id, g_world, client_fd);
		else
			quest->done_missions += kill(mission->goal_id, g_world);
		i++;
	}
	if (quest->done_missions == quest->missions.len)
		quest->done = 1;
}

int	cmd_complete_quest(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	if (!in(test.message, get_player_by_fd(client_fd, g_world)->quests))
		strcpy(result->message, "ERR 404 QUEST_NOT_FOUND\n");
	else
	{
		complete_quest(get_quest_by_id(test.message, g_world), g_world,
			client_fd);
		log_date();
		printf("Actualizing quest %s\n", test.message);
		strcpy(result->message, "OK done_missions=");
		strcat_number(result->message, get_quest_by_id(test.message,
				g_world)->done_missions);
		strcat(result->message, "\n");
		if (get_quest_by_id(test.message, g_world)->done
			&& strcmp(get_quest_by_id(test.message, g_world)->reward_id,
				"none"))
		{
			append_in(get_quest_by_id(test.message, g_world)->reward_id,
				&get_room_by_player_fd(client_fd, g_world)->items);
			util_left(g_world, result);
		}
	}
	return (1);
}
