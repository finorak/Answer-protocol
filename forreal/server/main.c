/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 12:41:16 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/15 10:24:41 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_utils.h"
#include <signal.h>

t_socket_property	g_server;
t_world				g_world;

static void	handle_shutdown(int sig)
{
	log_date();
	printf("shutdown...\n");
	close(g_server.server_fd);
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
			log_date();
			printf("Player %d DISCONNECTED\n", player_id(client_id, g_world));
			remove_player(client_id, &g_world);
			break ;
		}
		log_date();
		buf[strlen(buf) - 1] = '\0';
		printf("RECEIVED '%s' FROM PLAYER %d\n", buf, player_id(client_id,
				g_world));
		rec = val_exec(client_id, buf, &g_world);
		server_act(&rec, client_id);
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
	client_fd = accept(g_server.server_fd, (struct sockaddr *)&client_addr,
			&addr_len);
	if (client_fd < 0)
		return ;
	send(client_fd, "OK hello proto=1\n", 18, 0);
	add_player(client_fd, &g_world);
	inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
	log_date();
	printf("Player %d is CONNECTED (%s)\n", player_id(client_fd, g_world),
		client_ip);
	pthread_create(&client_mess_rec, NULL, client_host,
		(void *)(long)client_fd);
	pthread_detach(client_mess_rec);
}

int	main(void)
{
	log_date();
	printf("Server IP address: ");
	print_ip_addr();
	define_server_property(&g_server);
	signal(SIGINT, handle_shutdown);
	signal(SIGTERM, handle_shutdown);
	bind(g_server.server_fd, (struct sockaddr *)&(g_server.address),
		sizeof(g_server.address));
	listen(g_server.server_fd, 128);
	initialize_world(&g_world);
	log_date();
	printf("Server is initialized\n");
	while (1)
		server_routine();
}
