/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:26 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/14 10:28:26 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

static void	move(t_room *current_room, int ids, t_world *g_world,
		t_signal *result)
{
	char	str_id[12];

	sprintf(str_id, "%d", ids / MAX_LIST_LEN);
	strcpy(result->message, "OK room=");
	strcat(result->message, current_room->exits.ids[ids % MAX_LIST_LEN]);
	strcat(result->message, "\n");
	remove_from(str_id, &(current_room->players));
	append_in(str_id, &(get_room_by_id(current_room->exits.ids[ids % MAX_LIST_LEN],
				g_world)->players));
	log_date();
	printf("%s removed from '%s' and added to '%s'\n", get_player_by_fd(ids
			/ MAX_LIST_LEN, g_world)->name, current_room->id, current_room->exits.ids[ids
		% MAX_LIST_LEN]);
	result->players_0 = current_room->players;
	result->players_1 = get_room_by_id(current_room->exits.ids[ids % MAX_LIST_LEN],
			g_world)->players;
	strcpy(result->messages_0, "EVT ROOM PRESENCE LEAVE ");
	strcat(result->messages_0, get_player_by_fd(ids / MAX_LIST_LEN, g_world)->name);
	strcat(result->messages_0, "\n");
	strcpy(result->messages_1, "EVT ROOM PRESENCE ENTER ");
	strcat(result->messages_1, get_player_by_fd(ids / MAX_LIST_LEN, g_world)->name);
	strcat(result->messages_1, "\n");
}

int	cmd_move(t_command test, int client_fd, t_world *g_world, t_signal *result)
{
	char	dirs[4][6];
	int		dir_id;

	strcpy(dirs[0], "north");
	strcpy(dirs[1], "south");
	strcpy(dirs[2], "west");
	strcpy(dirs[3], "east");
	dir_id = 0;
	while (dir_id < 4)
	{
		if (!strcmp(dirs[dir_id], test.message)
			&& strcmp(get_room_by_player_fd(client_fd,
					g_world)->exits.ids[dir_id], "none"))
		{
			move(get_room_by_player_fd(client_fd, g_world), dir_id + MAX_LIST_LEN
				* client_fd, g_world, result);
			return (1);
		}
		dir_id++;
	}
	strcpy(result->message, "ERR 301 NO_EXIT\n");
	return (1);
}
