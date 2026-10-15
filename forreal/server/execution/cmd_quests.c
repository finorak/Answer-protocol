/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:36 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/15 17:04:17 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

static void add_quest(char *message, char *quest_id, t_world *g_world)
{
	t_quest *quest;

	quest = get_quest_by_id(quest_id, g_world);
	strcat(message, "{\"quest_id\": ");
	strcat_double_quoted(message, quest->id);
	strcat(message, ", \"status\": ");
	if (quest->done == 1)
		strcat_double_quoted(message, "active");
	else
		strcat_double_quoted(message, "inactive");
	// LEFT HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	strcat(message, "}");
}

int	cmd_quests(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	int	i;

	i = 0;
	strcpy(result->message, "OK [");
	while (i < get_player_by_fd(client_fd, g_world)->quests.len)
	{
		if (i != 0)
			strcat(result->message, ", ");
		add_quest(result->message, get_player_by_fd(client_fd,
				g_world)->quests.ids[i], g_world);
		i++;
	}
	strcat(result->message, "]\n");
	return (1);
}
