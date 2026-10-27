/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   late_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 07:36:49 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/27 10:28:21 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_utils.h"
#include <string.h>

void	recv_f(t_client cli, t_data *g_data)
{
	log_date();
	ft_printf("RECEIVED '%s' FROM PLAYER %d (%s)\n",
		cli.buf, player_id(cli.id, *(g_data->world)),
		get_player_by_fd(cli.id, g_data->world)->name);
}

void	ft_send(int sock, char *buffer, size_t size, int sign)
{
	char buf[BUFFER_SIZE];

	log_date();
	strcpy(buf, buffer);
	buf[strlen(buf) - 1] = '\0';
	ft_printf("SENDING '%s' TO PLAYER (fd=%d)\n",
		buf, sock);
	send(sock, buffer, size, sign);
}
