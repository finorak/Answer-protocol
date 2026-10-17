/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_distribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 08:59:04 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 06:13:08 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

void	strcat_double_quoted(char *message, char *element)
{
	strcat(message, "\"");
	strcat(message, element);
	strcat(message, "\"");
}

int	connect_look_move_chat(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	int	i;

	i = strcmp(get_player_by_fd(client_fd, g_world)->name, "UNAUTHENTICATED");
	if (!strcmp(test.type, "CONNECT"))
		return (cmd_connect(test, client_fd, g_world, result));
	else if (!strcmp(test.type, "LOOK") && i)
		return (cmd_look(test, client_fd, g_world, result));
	else if (!strcmp(test.type, "MOVE") && i)
		return (cmd_move(test, client_fd, g_world, result));
	else if ((!strcmp(test.type, "CHATGLOBAL") || !strcmp(test.type, "CHATROOM")
			|| !strcmp(test.type, "CHATGROUP")) && i)
		return (cmd_chat(test, client_fd, g_world, result));
	else
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
	int	i;

	i = strcmp(get_player_by_fd(client_fd, g_world)->name, "UNAUTHENTICATED");
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
	else
		return (0);
}
