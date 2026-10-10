/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:53:10 by finorako          #+#    #+#             */
/*   Updated: 2026/10/10 18:34:53 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../../includes/parser.h"
#include "../../includes/world.h"

static char	**get_room_ids(t_data *data)
{
	t_all_rooms	*room_container;
	char		**room_ids;
	int			index;

	if (!data)
		return (NULL);
	room_container = data->rooms;
	if (!room_container)
		return (NULL);
	room_ids = (char **)calloc(room_container->len, sizeof(char *));
	if (!room_ids)
		return (NULL);
	index = 0;
	while (index < room_container->len)
	{
		room_ids[index] = extract_room_id(room_container->rooms[index]);
		if (!room_ids[index])
		{
			free_room_ids(room_ids, index);
			return (NULL);
		}
		index ++;
	}
	return (room_ids);
}

// verify if at least 8 room do intersect
bool	data_validator(t_data *data)
{
	char	**room_names;
	int		index;

	if (!data)
		return (false);
	room_names = get_room_ids(data);
	if (!room_names)
		return (false);
	index = 0;
	// get current exits
	// verify exits exist inside database or is none
	while (index < data->rooms->len)
	{
		printf("%s\n", room_names[index]);
		index++;
	}
	free_room_ids(room_names, index);
	return (true);
}
