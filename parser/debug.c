/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako </var/spool/mail/finorako>	    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:38:51 by finorako          #+#    #+#             */
/*   Updated: 2026/10/16 18:01:53 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/parser.h"
#include "../includes/world.h"
#include "../includes/debug.h"

void	print_exits(t_room *room)
{
	int	index;

	if (!room)
		return ;
	index = 0;
	printf("****%s: start*****\n", room->id);
	while (index < room->exits.len)
		printf("\t\t%s\n", room->exits.ids[index++]);
	printf("****%s: end*****\n", room->id);
}

void	exit_printer(t_all_rooms *container, char *room_id)
{
	t_room	*room;
	int		index;

	if (!container)
		return ;
	index = 0;
	if (room_id)
	{
		room = get_room_from_id(container, room_id);
		return (print_exits(room));
	}
	else
	{
		while (index < container->len)
			print_exits(container->rooms[index++]);
	}
}
