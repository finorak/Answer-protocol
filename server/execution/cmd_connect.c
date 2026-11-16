/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:06:44 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/21 19:10:20 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../main_utils.h"

int	cmd_connect(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	t_player	*player;
	int			index;

	if (!result || !g_world)
		return (1);
	player = get_player_by_fd(client_fd, g_world);
	index = 0;
	while (index < MAX_PLAYER)
	{
		if (!strcmp(g_world->players->players[index].name, test.message))
			return (strcpy(result->message, "ERR 201 NAME_IN_USE\n"), 1);
		index++;
	}
	log_date();
	ft_printf("INFO: Client ip %s has changed his name %s into %s\n",
		player->ip, player->name, test.message);
	strcpy(player->name, test.message);
	strcpy(result->message, "OK connected\n");
	mess(g_world);
	return (1);
}
