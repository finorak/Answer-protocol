#include "../main_utils.h"


void	mess(t_world *world)
{
	int i;
	char mess[BUFFER_SIZE];
	char temp[12];

	i = 0;
	strcpy(mess, "EVT STATS players=");
	sprintf(temp, "%d", world->players.len);
	strcat(mess, temp);
	strcat(mess, "\n");
	while (i < MAX_PLAYER)
	{
		if (world->players.players[i].fd != -1)
			send(world->players.players[i].fd, mess, strlen(mess), 0);
		i++;
	}
}

void	add_player(int client_fd, t_world *world)
{
	int i;
	char client_fd_char[12];

	i = 0;
	while (i < MAX_PLAYER)
	{
		if (world->players.players[i].status == 0)
		{
			world->players.players[i].fd = client_fd;
			world->players.players[i].status = 1;
			snprintf(client_fd_char, sizeof(client_fd_char), "%d", client_fd);
			world->players.len++;
			append_in(client_fd_char, &(world->rooms.rooms[0].players));
			return ;
		}
		i++;
	}
	log_date();
	printf("EXCEDED MAX_PLAYER (%d)\n", MAX_PLAYER);
	exit(0);
}

void	remove_player(int client_fd, t_world *world)
{
	t_room *room;
	t_player *player;
	char temp[12];

	player = get_player_by_fd(client_fd, world);
	room = get_room_by_player_fd(client_fd, world);
	snprintf(temp, sizeof(temp), "%d", player->fd);
	remove_from(temp, &(room->players));
	log_date();
	printf("REMOVED '%s' FROM room (%s)\n", player->name, room->name);
	merge(&(player->items), &(room->items));
	player->fd = -1;
	player->status = 0;
	log_date();
	printf("REMOVED '%s' FROM list of player\n", player->name);
	strcpy(player->name, "UNAUTHENTICATED");
	player->quests.len = 0;
	player->hp = 100;
	player->max_hp = 100;
	player->attack = 10;
	strcpy(player->status_hp, "healthy");
	world->players.len--;
	mess(world);
}
