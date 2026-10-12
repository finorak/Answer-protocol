#include "../main_utils.h"

t_player *get_player_by_fd(int client_fd, t_world *world)
{
    int i;

    i = 0;
    while (i < world->players.len)
    {
        if (world->players.players[i].fd == client_fd)
            return (&world->players.players[i]);
        i ++;
    }
    return (NULL);
}