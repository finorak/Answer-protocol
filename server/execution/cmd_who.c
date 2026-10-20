/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:53 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 20:06:40 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../main_utils.h"

int	cmd_who(t_command test, int client_fd, t_world *g_world, t_signal *result)
{
	char	len[12];

	if (!result || !g_world)
		return (0);
	(void)test;
	(void)client_fd;
	sprintf(len, "%d", g_world->players->len);
	strcpy(result->message, "OK players=");
	strcat(result->message, len);
	strcat(result->message, "\n");
	return (1);
}
