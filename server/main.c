/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 12:41:16 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/24 10:02:49 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "execution/execution.h"
#include "main_utils.h"
#include "tools/tools.h"
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_data		g_data = {0};

static void	handle_shutdown(int sig)
{
	(void)sig;
	log_date();
	ft_printf("shutdown...\n");
	pthread_mutex_lock(&g_data.trafic);
	close(g_data.server.server_fd);
	free_data(g_data.world, g_data.buffer, true);
	pthread_mutex_unlock(&g_data.trafic);
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
	t_client	cli;

	cli.id = (int)(long)arg;
	while (1)
	{
		memset(cli.buf, 0, sizeof(cli.buf));
		if (recv(cli.id, cli.buf, BUFFER_SIZE, 0) <= 0)
		{
			safe_lock(cli, &g_data);
			break ;
		}
		cli.buf[strlen(cli.buf) - 1] = '\0';
		pthread_mutex_lock(&g_data.trafic);
		ft_printf("RECEIVED '%s' FROM PLAYER %d\n", cli.buf, player_id(cli.id,
				*g_data.world));
		cli.rec = val_exec(cli.id, cli.buf, g_data.world);
		server_act(&cli.rec, cli.id);
		if (!player_in(cli.id, *g_data.world))
		{
			pthread_mutex_unlock(&g_data.trafic);
			break ;
		}
		pthread_mutex_unlock(&g_data.trafic);
	}
	return (close(cli.id), NULL);
}

static void	server_routine(void)
{
	t_server_routine	routine;

	routine.addr_len = sizeof(routine.client_addr);
	routine.client_fd = accept(g_data.server.server_fd,
			(t_sock *)&routine.client_addr, &routine.addr_len);
	if (routine.client_fd < 0)
		return ;
	send(routine.client_fd, "OK hello proto=1\n", 18, 0);
	pthread_mutex_lock(&g_data.trafic);
	if (add_player(routine.client_fd, g_data.world) == 0)
	{
		send(routine.client_fd, "ERR 900 CONNECTION_FAILED\n", 26, 0);
		pthread_mutex_unlock(&g_data.trafic);
		return ;
	}
	pthread_mutex_unlock(&g_data.trafic);
	inet_ntop(AF_INET, &routine.client_addr.sin_addr, routine.client_ip,
		sizeof(routine.client_ip));
	log_date();
	ft_printf("Player %d is CONNECTED (%s)\n", player_id(routine.client_fd,
			*g_data.world), routine.client_ip);
	pthread_create(&routine.client_mess_rec, NULL, client_host,
		(void *)(long)routine.client_fd);
	pthread_detach(routine.client_mess_rec);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_printf("run with %s <world.json>\n", argv[0]), 1);
	g_data.buffer = get_buffer(argv[1], get_buffer_size(argv[1]));
	g_data.world = (t_world *)calloc(1, sizeof(t_world));
	if (!init_world_data(g_data.world, g_data.buffer))
		return (free_data(g_data.world, g_data.buffer, false), 1);
	log_date();
	pthread_mutex_init(&g_data.trafic, NULL);
	ft_printf("Server IP address: ");
	print_ip_addr();
	define_server_property(&g_data.server);
	signal(SIGINT, handle_shutdown);
	signal(SIGTERM, handle_shutdown);
	if (bind(g_data.server.server_fd, (t_sock *)&(g_data.server.address),
			sizeof(g_data.server.address)) < 0)
		return (ft_printf("Error %d\n", errno), 1);
	listen(g_data.server.server_fd, 128);
	log_date();
	ft_printf("Server is initialized\n");
	while (1)
		server_routine();
	return (free_data(g_data.world, g_data.buffer, true), 0);
}
