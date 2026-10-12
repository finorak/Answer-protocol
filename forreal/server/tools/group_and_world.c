#include "../main_utils.h"

t_group	*get_group_by_name(char *name, t_world *world)
{
	int	i;

	i = -1;
	while (++i < world->groups.len)
	{
		if (!strcmp(world->groups.groups[i].name, name))
			return (&(world->groups.groups[i]));
	}
	return (NULL);
}

t_group	*get_group_by_player_name(char *player_name, t_world *world)
{
	int		i;
	char	player_id[12];

	i = -1;
    sprintf(player_id, "%d", get_id_by_name(player_name, world));
	while (++i < world->groups.len)
	{
		if (in(player_id, world->groups.groups[i].players) == 1)
			return (&(world->groups.groups[i]));
	}
	return (NULL);
}

t_group	*get_group_by_player_fd(int id, t_world *world)
{
    int		i;
	char	player_id[12];

	i = -1;
    sprintf(player_id, "%d", id);
	while (++i < world->groups.len)
	{
		if (in(player_id, world->groups.groups[i].players) == 1)
			return (&(world->groups.groups[i]));
	}
	return (NULL);
}
