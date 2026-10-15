/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_and_world.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:28:11 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/15 10:28:12 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

t_player	*get_player_by_fd(int client_fd, t_world *world)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		if (world->players.players[i].fd == client_fd)
			return (&(world->players.players[i]));
		i++;
	}
	return (NULL);
}

t_player	*get_player_by_name(char *name, t_world *world)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		if (!strcmp(world->players.players[i].name, name))
			return (&(world->players.players[i]));
		i++;
	}
	return (NULL);
}

int	get_id_by_name(char *name, t_world *world)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		if (!strcmp(world->players.players[i].name, name))
			return (world->players.players[i].fd);
		i++;
	}
	return (-1);
}
