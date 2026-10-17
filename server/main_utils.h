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

#pragma once
#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#include "execution/execution.h"
#include "tools/tools.h"
#include "validation/validation.h"

void		log_date(void);
void		define_server_property(t_socket_property *server_property);
void		print_ip_addr(void);
int			player_id(int client_fd, t_world world);

t_signal	val_exec(int client_fd, char *buf, t_world *world);
