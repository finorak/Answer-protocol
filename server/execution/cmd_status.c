/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:40 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 06:14:57 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

int	cmd_status(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	t_player	*player;

	(void)test;
	player = get_player_by_fd(client_fd, g_world);
	strcpy(result->message, "OK {\"hp\": ");
	strcat_number(result->message, player->hp);
	strcat(result->message, ", \"max_hp\": ");
	strcat_number(result->message, player->max_hp);
	strcat(result->message, ", \"status\": ");
	strcat_double_quoted(result->message, player->status_hp);
	strcat(result->message, " }\n");
	return (1);
}
