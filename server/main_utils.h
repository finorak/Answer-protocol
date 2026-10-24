/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2026/10/15 10:34:58 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/15 10:34:58 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_UTILS_H
# define MAIN_UTILS_H

# include <pthread.h>
# include <sys/socket.h>
# include <unistd.h>
# include "../ft_printf/ft_printf.h"

# define PORT 8080
# include "execution/execution.h"
# include "tools/tools.h"
# include "validation/validation.h"

typedef struct s_data
{
	t_socket_property	server;
	char				*buffer;
	t_world				*world;
	pthread_mutex_t		trafic;
}				t_data;

typedef struct s_client
{
	int			client_id;
	char		buf[BUFFER_SIZE];
	t_signal	rec;
}				t_client;

typedef struct sockaddr	t_sock;

void		log_date(void);
void		define_server_property(t_socket_property *server_property);
void		print_ip_addr(void);
int			player_id(int client_fd, t_world world);

t_signal	val_exec(int client_fd, char *buf, t_world *world);

// helper for group as the 25 lines suck
void		cpy(t_signal *result, t_command test);

#endif
