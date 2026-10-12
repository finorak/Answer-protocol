/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 06:28:45 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/12 06:36:48 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

void	add_player(int client_fd, t_world *world)
{
	int i;
	char client_fd_char[4];

	i = 0;
	while (i < MAX_PLAYER)
	{
		if (world->players.players[i].status == 0)
		{
			world->players.players[i].fd = client_fd;
			world->players.players[i].status = 1;
			snprintf(client_fd_char, "%d", client_fd);
			append_in(client_fd_char, &(world->rooms.rooms[0].players));
			return ;
		}
		i++;
	}
	log_date();
	printf("EXCEDED MAX_PLAYER (%d)\n", MAX_PLAYER);
	exit(0);
}

void	remove_player(int client_fd, t_world *world)
{
}
