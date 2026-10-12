#include "../main_utils.h"

t_room	*get_room_by_id(int room_id, t_world *world)
{
	int	i;

	i = -1;
	while (++i < world->rooms.len)
	{
		if (world->rooms.rooms[i].id == room_id)
			return (&(world->rooms.rooms[i]));
	}
	return (NULL);
}

t_room	*get_room_by_player_fd(int client_fd, t_world *world)
{
	int	i;
	int	j;

	i = -1;
	while (++i < world->rooms.len)
	{
		j = -1;
		while (++j < world->rooms.rooms[i].players.len)
		{
			if (atoi(world->rooms.rooms[i].players.ids[j]) == client_fd)
				return (&(world->rooms.rooms[i]));
		}
	}
	return (NULL);
}

t_room	*get_room_by_item_id(int item_id, t_world *world)
{
	int	i;
	int	j;

	i = -1;
	while (++i < world->rooms.len)
	{
		j = -1;
		while (++j < world->rooms.rooms[i].items.len)
		{
			if (atoi(world->rooms.rooms[i].items.ids[j]) == item_id)
				return (&(world->rooms.rooms[i]));
		}
	}
	return (NULL);
}

t_room	*get_room_by_npc_id(int npc_id, t_world *world)
{
	int	i;
	int	j;

	i = -1;
	while (++i < world->rooms.len)
	{
		j = -1;
		while (++j < world->rooms.rooms[i].npcs.len)
		{
			if (atoi(world->rooms.rooms[i].npcs.ids[j]) == npc_id)
				return (&(world->rooms.rooms[i]));
		}
	}
	return (NULL);
}
