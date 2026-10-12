#include "../main_utils.h"

t_player	*get_player_by_fd(int client_fd, t_world *world)
{
	int	i;

	i = 0;
	while (i < world->players.len)
	{
		if (world->players.players[i].fd == client_fd)
			return (&(world->players.players[i]));
		i++;
	}
	return (NULL);
}

t_player	*get_player_by_name(char *name, t_world *world)
{
	int	i;

	i = 0;
	while (i < world->players.len)
	{
		if (!strcmp(world->players.players[i].name, name))
			return (&(world->players.players[i]));
		i++;
	}
	return (NULL);
}

int	get_id_by_name(char *name, t_world *world)
{
	int	i;

	i = 0;
	while (i < world->players.len)
	{
		if (!strcmp(world->players.players[i].name, name))
			return (world->players.players[i].fd);
		i++;
	}
	return (-1);
}
