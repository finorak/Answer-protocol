/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_drop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:07 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/15 11:54:41 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

int	cmd_drop(t_command test, int client_fd, t_world *g_world, t_signal *result)
{
	char	temp[12];

	if (get_player_by_item(test.message, g_world) == NULL
		|| get_player_by_item(test.message, g_world)->fd != client_fd)
		strcpy(result->message, "404 ITEM_NOT_IN_INVENTORY\n");
	else
	{
		append_in(test.message, &(get_room_by_player_fd(client_fd,
					g_world)->items));
		log_date();
		printf("added %s to %s\n", test.message,
			get_room_by_item_id(test.message, g_world)->name);
		remove_from(test.message, &(get_player_by_item(test.message,
					g_world)->items));
		strcpy(result->message, "OK dropped=");
		strcat(result->message, test.message);
		strcat(result->message, "\n");
		fill_with_all(result, g_world);
		all_items_left(g_world, temp);
		strcpy(result->messages_0, "EVT STATS items=");
		strcat(result->messages_0, temp);
		strcat(result->messages_0, "\n");
	}
	return (1);
}
