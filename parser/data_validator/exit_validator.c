/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 09:06:23 by finorako          #+#    #+#             */
/*   Updated: 2026/10/18 14:14:11 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>
#include "../../includes/world.h"

bool	key_exist(char *key, char **room_ids)
{
	int	index;

	if (!room_ids)
		return (false);
	index = 0;
	while (room_ids[index])
	{
		if (strcmp(key, room_ids[index]) == 0)
			return (true);
		index ++;
	}
	return (false);
}

static bool	exit_valid(t_room *curr_room, char **room_ids)
{
	char	*key;
	int		index;

	if (!curr_room)
		return (false);
	index = 0;
	while (index < curr_room->exits.len)
	{
		key = curr_room->exits.ids[index];
		if (strcmp(key, "none") == 0)
		{
			index ++;
			continue ;
		}
		if (
			!*key || strcmp(key, curr_room->id) == 0
			|| !key_exist(key, room_ids)
		)
			return (false);
		index ++;
	}
	return (true);
}

bool	verify_exit(t_world *data, char **room_ids)
{
	t_room	*curr_room;
	int		index;

	if (!data || !data->extract)
		return (false);
	index = 0;
	while (index < data->rooms->len)
	{
		curr_room = data->rooms->rooms[index];
		if (!exit_valid(curr_room, room_ids))
			return (false);
		index ++;
	}
	return (true);
}
