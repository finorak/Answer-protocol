/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_inventory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:15 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/15 16:12:33 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

int	cmd_inventory(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	strcpy(result->message, "OK ");
	concat_into_message(result->message, get_player_by_fd(client_fd, g_world)->items, 0, g_world);
	strcat(result->message, "\n");
	return (1);
}
