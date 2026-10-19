/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_distribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 08:59:04 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 20:06:10 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../main_utils.h"

void	strcat_double_quoted(char *message, char *element)
{
	strcat(message, "\"");
	strcat(message, element);
	strcat(message, "\"");
}

int	connect_look_move_chat(t_command command, int client_fd, t_world *g_world,
		t_signal *result)
{
	t_player	*player;
	int			i;

	player = get_player_by_fd(client_fd, g_world);
	if (!player)
		return (0);
	i = strcmp(player->name, "UNAUTHENTICATED");
	if (!strcmp(command.type, "CONNECT"))
		return (cmd_connect(command, client_fd, g_world, result));
	else if (!strcmp(command.type, "LOOK") && i)
		return (cmd_look(command, client_fd, g_world, result));
	else if (!strcmp(command.type, "MOVE") && i)
		return (cmd_move(command, client_fd, g_world, result));
	else if ((!strcmp(command.type, "CHATGLOBAL")
			|| !strcmp(command.type, "CHATROOM")
			|| !strcmp(command.type, "CHATGROUP")) && i)
		return (cmd_chat(command, client_fd, g_world, result));
	return (0);
}

int	who_group_item(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	int	i;

	i = strcmp(get_player_by_fd(client_fd, g_world)->name, "UNAUTHENTICATED");
	if (!strcmp(test.type, "WHO") && i)
		return (cmd_who(test, client_fd, g_world, result));
	else if ((!strcmp(test.type, "GROUPCREATE") || !strcmp(test.type,
				"GROUPINVITE") || !strcmp(test.type, "GROUPJOIN")
			|| !strcmp(test.type, "GROUPLEAVE")) && i)
		return (cmd_group(test, client_fd, g_world, result));
	else if (!strcmp(test.type, "TAKE") && i)
		return (cmd_take(test, client_fd, g_world, result));
	else if (!strcmp(test.type, "DROP") && i)
		return (cmd_drop(test, client_fd, g_world, result));
	else if (!strcmp(test.type, "INVENTORY") && i)
		return (cmd_inventory(test, client_fd, g_world, result));
	else
		return (0);
}

int	talk_attack_status_quest(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	t_player	*player;
	int			i;

	player = get_player_by_fd(client_fd, g_world);
	if (!player)
		return (0);
	i = strcmp(player->name, "UNAUTHENTICATED");
	if (!strcmp(test.type, "TALK") && i)
		return (cmd_talk(test, client_fd, g_world, result));
	else if ((!strcmp(test.type, "ATTACK")) && i)
		return (cmd_attack(test, client_fd, g_world, result));
	else if (!strcmp(test.type, "STATUS") && i)
		return (cmd_status(test, client_fd, g_world, result));
	else if (!strcmp(test.type, "QUEST") && i)
		return (cmd_quest(test, client_fd, g_world, result));
	else if (!strcmp(test.type, "QUESTS") && i)
		return (cmd_quests(test, client_fd, g_world, result));
	else if (!strcmp(test.type, "COMPLETE_QUEST") && i)
		return (cmd_complete_quest(test, client_fd, g_world, result));
	return (0);
}
