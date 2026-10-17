/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:31 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 20:07:48 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../main_utils.h"

static void	ok_quest(t_quest *quest, int client_fd, t_world *g_world,
		t_signal *result)
{
	log_date();
	printf("power off quest:%s from npc:%s\n", quest->id, quest->npc_owner_id);
	quest->available = 0;
	append_in(quest->id, &get_player_by_fd(client_fd, g_world)->quests);
	strcpy(result->message, "OK {\"quest_id\": ");
	strcat_double_quoted(result->message, quest->id);
	strcat(result->message, ", \"description\": ");
	strcat_double_quoted(result->message, quest->description);
	if (strcmp(quest->reward_id, "none"))
	{
		strcat(result->message, ", \"reward\": ");
		strcat_double_quoted(result->message, quest->reward_id);
	}
	strcat(result->message, "}\n");
}

int	cmd_quest(t_command test, int client_fd, t_world *g_world, t_signal *result)
{
	t_npc	*npc;
	t_quest	*quest;

	npc = get_npc_by_id(test.message, g_world);
	if (npc == NULL || !(in(npc->id, get_room_by_player_fd(client_fd,
					g_world)->npcs)))
		strcpy(result->message, "ERR 404 NPC_NOT_FOUND\n");
	else
	{
		quest = get_quest_by_id(npc->quest_id, g_world);
		if (quest == NULL || quest->available == 0 || quest->done == 1)
			strcpy(result->message, "ERR 406 NO_QUEST_AVAILABLE\n");
		else
			ok_quest(quest, client_fd, g_world, result);
	}
	return (1);
}
