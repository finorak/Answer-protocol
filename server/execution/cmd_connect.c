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

#include <stdio.h>
#include <string.h>
#include "../main_utils.h"

int	cmd_connect(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	int	i;

	if (!result || !g_world)
		return (0);
	i = 0;
	while (i < MAX_PLAYER)
	{
		if (!strcmp(g_world->players->players[i].name, test.message))
		{
			strcpy(result->message, "ERR 201 NAME_IN_USE\n");
			return (1);
		}
		i++;
	}
	log_date();
	printf("Client fd %d has changed his name %s into %s\n", client_fd,
		get_player_by_fd(client_fd, g_world)->name, test.message);
	strcpy(get_player_by_fd(client_fd, g_world)->name, test.message);
	strcpy(result->message, "OK connected\n");
	mess(g_world);
	return (1);
}
