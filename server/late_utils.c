/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   late_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 07:36:49 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/27 12:39:48 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_utils.h"
#include "tools/tools.h"
#include <ctype.h>
#include <string.h>

void	recv_f(t_client cli, t_data *g_data)
{
	t_player	*player;

	player = get_player_by_fd(cli.id, g_data->world);
	log_date();
	ft_printf("INFO: RECEIVED '%s' FROM PLAYER %d (%s)\n",
		cli.buf, player_id(cli.id, *(g_data->world)),
		player->ip);
}

static char	*info_header(const char *buffer)
{
	if (strncmp(buffer, "ERR", 3) == 0)
		return ("ERROR");
	if (*buffer && isdigit(buffer[0]))
		return ("ERROR");
	return ("INFO");
}

void	ft_send(int sock, const char *buffer, t_world *world, int sign)
{
	t_player	*player;
	char		buf[BUFFER_SIZE];
	int			size;

	player = get_player_by_fd(sock, world);
	log_date();
	size = strlen(buffer);
	strcpy(buf, buffer);
	buf[strlen(buf) - 1] = '\0';
	ft_printf("%s: SENDING '%s' TO PLAYER (ip=%s)\n",
		info_header(buf), buf, player->ip);
	send(sock, buffer, size, sign);
}
