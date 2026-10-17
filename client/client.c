/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 06:53:12 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 21:25:13 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include <stdio.h>

static atomic_int	g_disconnect = 0;

static void	*wait_for_server(void *arg)
{
	char	buffer[BUFFER_SIZE];
	int		sock;

	sock = *(int *)(arg);
	while (1)
	{
		memset(buffer, 0, BUFFER_SIZE);
		if (g_disconnect == 1)
			break ;
		if (recv(sock, buffer, BUFFER_SIZE, 0) <= 0)
		{
			g_disconnect = 1;
			break ;
		}
		printf("\r%s", buffer);
	}
	return (NULL);
}

static void	*wait_for_user(void *arg)
{
	char	buffer[BUFFER_SIZE];
	int		sock;

	sock = *(int *)(arg);
	buffer[0] = '\0';
	while (1)
	{
		if (!strcmp(buffer, "QUIT\n"))
			g_disconnect = 1;
		if (g_disconnect == 1)
			break ;
		memset(buffer, 0, BUFFER_SIZE);
		printf("\rC: ");
		fgets(buffer, BUFFER_SIZE, stdin);
		send(sock, buffer, strlen(buffer), 0);
	}
	return (NULL);
}

static int	end(int sock)
{
	close(sock);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t			client_mods[2];
	int					sock;
	struct sockaddr_in	addr;

	if (argc != 2)
	{
		printf("Please use the format ./client <server-ip-addr>\n");
		return (1);
	}
	printf("%s\n", argv[1]);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		printf("ERR 900 CONNECTION_FAILED\n");
		return (end(sock));
	}
	pthread_create(&(client_mods[0]), NULL, wait_for_server, &sock);
	pthread_create(&(client_mods[1]), NULL, wait_for_user, &sock);
	pthread_join(client_mods[0], NULL);
	pthread_join(client_mods[1], NULL);
	return (end(sock));
}
