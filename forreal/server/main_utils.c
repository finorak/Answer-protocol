#include "main_utils.h"

void	log_date(void)
{
	time_t	timestamp;
	char	*date;

	timestamp = time(NULL);
	date = ctime(&timestamp);
	date[strlen(date) - 1] = '\0';
	printf("\r[%s] - ", date);
}

void	print_ip_addr(void)
{
	char			hostname[256];
	struct hostent	*host_entry;
	char			ip[INET_ADDRSTRLEN];

	gethostname(hostname, sizeof(hostname));
	host_entry = gethostbyname(hostname);
	inet_ntop(AF_INET, host_entry->h_addr_list[0], ip, sizeof(ip));
	printf("%s\n", ip);
}

void	define_server_property(t_socket_property *server_property)
{
	server_property->server_fd = socket(AF_INET, SOCK_STREAM, 0);
	server_property->address.sin_family = AF_INET;
	server_property->address.sin_addr.s_addr = INADDR_ANY;
	server_property->address.sin_port = htons(PORT);
}

int		player_id(int client_fd, t_world world)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		if (world.players.players[i].fd == client_fd)
			return (i + 1);
		else
			i++;
	}
	return (0);
}
