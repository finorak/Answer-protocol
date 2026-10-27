/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 06:53:12 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/27 09:02:38 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "client.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"

static atomic_int	g_disconnect = 0;

static void	print_buffer(char **strings, char header)
{
	int	index;

	if (!strings)
		return ;
	if (!*strings)
	{
		free(strings);
		return ;
	}
	index = 0;
	while (strings[index])
	{
		ft_printf("\r%c: %s\n", header, strings[index]);
		free(strings[index]);
		index++;
	}
	free(strings);
	ft_printf("\rC: ");
}

static void	*wait_for_server(void *arg)
{
	char	buffer[BUFFER_SIZE];
	char	**strings;
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
		strings = ft_split(buffer, '\n');
		if (!strcmp(strings[0], "ERR 900 CONNECTION_FAILED"))
			g_disconnect = 1;
		print_buffer(strings, 'S');
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
		if (!fgets(buffer, BUFFER_SIZE, stdin))
			continue ;
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
		fprintf(stderr, "Please use the format ./client <server-ip-addr>\n");
		return (1);
	}
	printf("%s\n", argv[1]);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		fprintf(stderr, "ERR 900 CONNECTION_FAILED\n");
		g_disconnect = 1;
		return (end(sock));
	}
	pthread_create(&(client_mods[0]), NULL, wait_for_server, &sock);
	pthread_create(&(client_mods[1]), NULL, wait_for_user, &sock);
	pthread_join(client_mods[0], NULL);
	pthread_join(client_mods[1], NULL);
	return (end(sock));
}
