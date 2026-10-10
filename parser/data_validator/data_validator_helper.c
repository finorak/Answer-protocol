/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validator_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako  </var/spool/mail/finorako>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 17:30:47 by finorako          #+#    #+#             */
/*   Updated: 2026/10/10 18:35:50 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "../../includes/parser.h"
#include "../../includes/world.h"

// Freeing room ids
void	free_room_ids(char **room_ids, int size)
{
	int	index;

	if (!room_ids)
		return ;
	index = 0;
	while (index < size)
	{
		free(room_ids[index]);
		index ++;
	}
	free(room_ids);
}

/*
*
*/
char	*extract_room_id(t_room *room)
{
	char	*room_id;
	int		size;

	if (!room)
		return (NULL);
	size = strlen(room->id);
	room_id = (char *)calloc(size + 1, sizeof(char));
	if (!room_id)
		return (NULL);
	strncpy(room_id, room->id, size);
	return (room_id);
}
