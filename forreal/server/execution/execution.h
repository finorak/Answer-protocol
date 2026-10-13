int connect_look_move_chat(t_command test, int client_fd, t_world *g_world, t_signal *result);
int who_group_item(t_command test, int client_fd, t_world *g_world, t_signal *result);
int talk_attack_status_quest(t_command test, int client_fd, t_world *g_world, t_signal *result);

t_signal	execution(t_command test, int client_fd, t_world *g_world);
