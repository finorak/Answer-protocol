/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_talk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:49 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 20:07:03 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../main_utils.h"

int	cmd_talk(t_command test, int client_fd, t_world *g_world, t_signal *result)
{
	t_npc		*npc;
	t_dialogue	*dialogue;

	(void)test;
	(void)client_fd;
	npc = get_npc_by_id(test.message, g_world);
	if (!npc)
	{
		strcpy(result->message, "ERR 404 NPC_NOT_FOUND\n");
		return (1);
	}
	dialogue = get_dialogue_by_id(npc->dialogues.ids[npc->dialogue_index],
			g_world);
	strcpy(result->message, "OK { \"npc\": ");
	strcat_double_quoted(result->message, npc->id);
	strcat(result->message, ", \"dialogue\": ");
	strcat_double_quoted(result->message, dialogue->content);
	strcat(result->message, " }\n");
	log_date();
	printf("dialogue_index = (dialogue_index + 1) mod(dialogue_len)");
	npc->dialogue_index = (npc->dialogue_index + 1) % npc->dialogues.len;
	return (1);
}
