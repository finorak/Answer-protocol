/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:06:44 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/13 09:34:59 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

int	cmd_connect(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	int	i;

	i = 0;
	while (i < g_world->players.len)
	{
		if (!strcmp(g_world->players.players[i].name, test.message))
		{
			strcpy(result->message, "ERR 201 NAME_IN_USE\n");
			return (1);
		}
		i++;
	}
	strcpy(get_player_by_fd(client_fd, g_world)->name, test.message);
	strcpy(result->message, "OK connected\n");
	return (1);
}
