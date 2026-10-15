/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 08:58:49 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/15 10:34:17 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		strcat_double_quoted(char *message, char *element);

int			cmd_connect(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_look(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_move(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_chat(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_who(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_group(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_take(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_drop(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_inventory(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_talk(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_attack(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_status(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_quest(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_quests(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			cmd_abandon_quest(t_command test, int client_fd, t_world *g_world,
				t_signal *result);

int			connect_look_move_chat(t_command test, int client_fd,
				t_world *g_world, t_signal *result);
int			who_group_item(t_command test, int client_fd, t_world *g_world,
				t_signal *result);
int			talk_attack_status_quest(t_command test, int client_fd,
				t_world *g_world, t_signal *result);

t_signal	execution(t_command test, int client_fd, t_world *g_world);
