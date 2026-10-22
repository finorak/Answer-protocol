/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   late_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:43:57 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/21 19:10:04 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../../includes/world.h"
#include <stdio.h>

void	strcat_number(char *message, int number)
{
	char	temp[12];

	sprintf(temp, "%d", number);
	strcat(message, temp);
}

int	player_in(int client_fd, t_world g_world)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		if (client_fd == g_world.players->players[i].fd)
			return (1);
		i++;
	}
	return (0);
}
