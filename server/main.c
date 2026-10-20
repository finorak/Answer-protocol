/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 12:41:16 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/20 08:42:54 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../includes/parser.h"
#include "main_utils.h"

t_data	g_data = {0};

static void	handle_shutdown(int sig)
{
	(void)sig;
	log_date();
	printf("shutdown...\n");
	close(g_data.server.server_fd);
	free_data(g_data.world, g_data.buffer, true);
	exit(0);
}

static void	server_act(t_signal *rec, int client_fd)
{
	int	i;

	i = 0;
	send(client_fd, rec->message, strlen(rec->message), 0);
	while (i < rec->players_0.len)
	{
		send(atoi(rec->players_0.ids[i]), rec->messages_0,
			strlen(rec->messages_0), 0);
		i++;
	}
	i = 0;
	while (i < rec->players_1.len)
	{
		send(atoi(rec->players_1.ids[i]), rec->messages_1,
			strlen(rec->messages_1), 0);
		i++;
	}
	memset(rec->message, 0, sizeof(rec->message));
	rec->players_0.len = 0;
	rec->players_1.len = 0;
}

static void	*client_host(void *arg)
{
	int			client_id;
	char		buf[BUFFER_SIZE];
	t_signal	rec;

	client_id = (int)(long)arg;
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		if (recv(client_id, buf, BUFFER_SIZE, 0) <= 0)
		{
			remove_player(client_id, g_data.world);
			break ;
		}
		log_date();
		buf[strlen(buf) - 1] = '\0';
		printf("RECEIVED '%s' FROM PLAYER %d\n", buf, player_id(client_id,
				*g_data.world));
		rec = val_exec(client_id, buf, g_data.world);
		server_act(&rec, client_id);
		if (!player_in(client_id, *g_data.world))
			break ;
	}
	close(client_id);
	return (NULL);
}

static void	server_routine(void)
{
	pthread_t			client_mess_rec;
	int					client_fd;
	char				client_ip[INET_ADDRSTRLEN];
	struct sockaddr_in	client_addr;
	socklen_t			addr_len;

	addr_len = sizeof(client_addr);
	client_fd = accept(g_data.server.server_fd, (struct sockaddr *)&client_addr,
			&addr_len);
	if (client_fd < 0)
		return ;
	send(client_fd, "OK hello proto=1\n", 18, 0);
	add_player(client_fd, g_data.world);
	inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
	log_date();
	printf("Player %d is CONNECTED (%s)\n", player_id(client_fd, *g_data.world),
		client_ip);
	pthread_create(&client_mess_rec, NULL, client_host,
		(void *)(long)client_fd);
	pthread_detach(client_mess_rec);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (fprintf(stderr, "run with %s <world.json>\n", argv[0]), 1);
	g_data.buffer = get_buffer(argv[1], get_buffer_size(argv[1]));
	g_data.world = (t_world *)calloc(1, sizeof(t_world));
	log_date();
	printf("Server IP address: ");
	print_ip_addr();
	define_server_property(&g_data.server);
	signal(SIGINT, handle_shutdown);
	signal(SIGTERM, handle_shutdown);
	bind(g_data.server.server_fd, (struct sockaddr *)&(g_data.server.address),
		sizeof(g_data.server.address));
	listen(g_data.server.server_fd, 128);
	if (!init_world_data(g_data.world, g_data.buffer))
		return (free_data(g_data.world, g_data.buffer, false), 1);
	log_date();
	printf("Server is initialized\n");
	while (1)
		server_routine();
	return (free_data(g_data.world, g_data.buffer, true), 0);
}
