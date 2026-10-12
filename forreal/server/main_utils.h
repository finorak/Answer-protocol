#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

// include socket, etc...

#include "init_world.h"
#include "validation/validation.h"
#include "tools/tools.h"
#include "execution/execution.h"
#define BUFFER_SIZE 1024
#define PORT 8080


typedef struct s_socket_property
{
	int					server_fd;
	struct sockaddr_in	address;
}						t_socket_property;

typedef struct s_signal
{
	t_list_of players_0;
	char	  messages_0[BUFFER_SIZE];
	t_list_of players_1;
	char 	  messages_1[BUFFER_SIZE];
	char 	  message[BUFFER_SIZE];
}						t_signal;

typedef struct s_command
{
	int					is_valid;
	char				type[32];
	char				message[128];
}						t_command;

void	log_date(void);
void	define_server_property(t_socket_property *server_property);
void	print_ip_addr(void);
int		player_id(int client_fd, t_world world);

t_signal val_exec(int client_fd, char *buf, t_world *world);
