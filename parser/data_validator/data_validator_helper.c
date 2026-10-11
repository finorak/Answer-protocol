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

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/parser.h"
#include "../../includes/world.h"

/*
* Extracting ids so that we can just verify
* the interconection of the rooms
*/
char	*extract_room_id(char *room_id)
{
	char	*string;
	int		size;

	// printf("((%s))\n", room_id);
	if (!room_id)
		return (NULL);
	size = strlen(room_id);
	// printf("%d | %s | -> ", size, room_id);
	string = (char *)calloc(size + 1, sizeof(char));
	if (!string)
		return (NULL);
	strncpy(string, room_id, size);
	return (string);
}

bool	key_is_reconnecting(char *curr_id, t_list_of exits)
{
	int	index;

	index = 0;
	while (index < exits.len)
	{
		if (strcmp(curr_id, exits.ids[index]) == 0)
		{
			return (false);
		}
		index++;
	}
	return (true);
}
