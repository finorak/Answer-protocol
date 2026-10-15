/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_chat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:34:45 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/15 10:33:24 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

static void	fill_with_all(t_signal *result, t_world *g_world)
{
	int		i;
	int		index;
	char	temp[12];

	i = 0;
	index = 0;
	while (i < MAX_PLAYER)
	{
		if (g_world->players.players[i].fd != -1)
		{
			snprintf(temp, sizeof(temp), "%d", g_world->players.players[i].fd);
			strcpy(result->players_0.ids[index], temp);
			index++;
		}
		i++;
	}
	result->players_0.len = index;
}

static void	transform(char *temp, char *type)
{
	if (type[4] == 'G' && type[5] == 'L')
		strcpy(temp, "GLOBAL");
	else if (type[4] == 'R')
		strcpy(temp, "ROOM");
	else
		strcpy(temp, "GROUP");
}

int	cmd_chat(t_command test, int client_fd, t_world *g_world, t_signal *result)
{
	char	temp[8];

	transform(temp, test.type);
	strcpy(result->message, "OK\n");
	strcpy(result->messages_0, "EVT ");
	strcat(result->messages_0, temp);
	strcat(result->messages_0, " CHAT ");
	strcat(result->messages_0, get_player_by_fd(client_fd, g_world)->name);
	strcat(result->messages_0, " ");
	strcat(result->messages_0, test.message);
	strcat(result->messages_0, "\n");
	if (!strcmp(test.type, "CHATGLOBAL"))
		fill_with_all(result, g_world);
	else if (!strcmp(test.type, "CHATROOM"))
		result->players_0 = get_room_by_player_fd(client_fd, g_world)->players;
	else
	{
		if (get_group_by_player_fd(client_fd, g_world) == NULL)
			strcpy(result->message, "ERR 401 NOT_IN_GROUP\n");
		else
			result->players_0 = get_group_by_player_fd(client_fd,
					g_world)->players;
	}
	return (1);
}
