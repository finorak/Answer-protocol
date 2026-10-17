/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_take.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:46 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 09:56:16 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

void	all_items_left(t_world *world, char *temp)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < world->rooms->len)
	{
		result += world->rooms->rooms[i].items.len;
		i++;
	}
	sprintf(temp, "%d", result);
}

int	cmd_take(t_command test, int client_fd, t_world *g_world, t_signal *result)
{
	char	temp[12];

	if (!in(test.message, get_room_by_player_fd(client_fd, g_world)->items))
		strcpy(result->message, "404 ITEM_NOT_FOUND\n");
	else
	{
		log_date();
		printf("removed %s from %s\n", test.message,
			get_room_by_item_id(test.message, g_world)->name);
		remove_from(test.message, &(get_room_by_item_id(test.message,
					g_world)->items));
		append_in(test.message, &(get_player_by_fd(client_fd, g_world)->items));
		strcpy(result->message, "OK taken=");
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
