/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:40 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/27 06:32:32 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../main_utils.h"

int	cmd_status(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	t_player	*player;

	if (!g_world)
		return (0);
	(void)test;
	player = get_player_by_fd(client_fd, g_world);
	if (!player)
		return (strcpy(result->message, "404 PLAYER_NOT_FOUND\n"), 1);
	strcpy(result->message, "OK {\"hp\": ");
	strcat_number(result->message, player->hp);
	strcat(result->message, ", \"max_hp\": ");
	strcat_number(result->message, player->max_hp);
	strcat(result->message, ", \"status\": ");
	strcat_double_quoted(result->message, player->status_hp);
	strcat(result->message, " }\n");
	return (1);
}
