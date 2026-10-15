/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2026/10/13 08:59:31 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/13 08:59:35 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

t_signal	execution(t_command test, int client_fd, t_world *g_world)
{
	t_signal	result;

	result.players_0.len = 0;
	result.players_1.len = 0;
	if (connect_look_move_chat(test, client_fd, g_world, &result) == 1)
		return (result);
	else if (who_group_item(test, client_fd, g_world, &result) == 1)
		return (result);
	else if (talk_attack_status_quest(test, client_fd, g_world, &result) == 1)
		return (result);
	else if (!strcmp(test.type, "QUIT"))
		strcpy(result.message, "OK bye\n");
	else
		strcpy(result.message, "ERR 401 UNAUTHORIZED\n");
	return (result);
}
