#pragma once
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define PORT 8080
#include "init_world.h"
#include "execution/execution.h"
#include "tools/tools.h"
#include "validation/validation.h"

void	log_date(void);
void	define_server_property(t_socket_property *server_property);
void	print_ip_addr(void);
int	player_id(int client_fd, t_world world);

t_signal	val_exec(int client_fd, char *buf, t_world *world);
