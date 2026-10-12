#include "../main_utils.h"

t_signal	execution(t_command test, int client_fd, t_world *g_world)
{
    t_signal result;

    result.players_0.len = 0;
    result.players_1.len = 0;
    strcpy(result.message, "type: ");
    strcat(result.message, test.type);
    strcat(result.message, ", message: ");
    strcat(result.message, test.message);
    strcat(result.message, "\n");
    return (result);
}
