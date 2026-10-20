/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_look.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:22 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 20:08:15 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../main_utils.h"

static void	exits_helper(char *message, char dirs[4][6], t_room *room, int i)
{
	strcat_double_quoted(message, dirs[i]);
	strcat(message, ": ");
	strcat_double_quoted(message, room->exits.ids[i]);
}

static void	exits(char *message, t_room *room)
{
	int		i;
	int		curr_available_room;
	char	dirs[4][6];

	if (!message || !room)
		return ;
	strcpy(dirs[0], "north");
	strcpy(dirs[1], "south");
	strcpy(dirs[2], "west");
	strcpy(dirs[3], "east");
	i = 0;
	curr_available_room = 0;
	strcat(message, "{");
	while (i < 4)
	{
		if (strcmp(room->exits.ids[i], "none"))
		{
			if (curr_available_room != 0)
				strcat(message, ", ");
			exits_helper(message, dirs, room, i);
			curr_available_room++;
		}
		i++;
	}
	strcat(message, "}");
}

static void	room(char *message, t_room *room)
{
	if (!message || !room)
		return ;
	strcat(message, "{ \"id\": ");
	strcat_double_quoted(message, room->id);
	strcat(message, ", \"name\": ");
	strcat_double_quoted(message, room->name);
	strcat(message, ", \"description\": ");
	strcat_double_quoted(message, room->description);
	strcat(message, ", \"exits\": ");
	exits(message, room);
	strcat(message, " }");
}

int	cmd_look(t_command test, int client_fd, t_world *g_world, t_signal *result)
{
	t_room	*room_;

	if (!g_world || !result)
		return (0);
	(void)test;
	room_ = get_room_by_player_fd(client_fd, g_world);
	strcpy(result->message, "OK { \"room\": ");
	room(result->message, room_);
	strcat(result->message, ", \"players\": ");
	concat_into_message(result->message, room_->players, 1, g_world);
	strcat(result->message, ", \"items\": ");
	concat_into_message(result->message, room_->items, 0, g_world);
	strcat(result->message, ", \"npcs\": ");
	concat_into_message(result->message, room_->npcs, 0, g_world);
	strcat(result->message, " }\n");
	return (1);
}
