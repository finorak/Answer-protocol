/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_group.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <rraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:35:11 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/21 19:10:07 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"
#include <stdio.h>
#include <string.h>

static void	grp_create(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	t_group	new_group;
	char	temp[12];

	sprintf(temp, "%d", client_fd);
	strcpy(new_group.name, test.message);
	strcpy(new_group.players.ids[0], temp);
	new_group.players.len = 1;
	if (get_group_by_name(test.message, g_world) != NULL)
		strcpy(result->message, "ERR 201 GROUP_NAME_IN_USE\n");
	else if (get_group_by_player_fd(client_fd, g_world) != NULL)
		strcpy(result->message, "ERR 402 ALREADY_IN_GROUP\n");
	else if (g_world->groups->len < MAX_LIST_LEN)
	{
		log_date();
		ft_printf("new group - %s (%s)\n", new_group.name,
			get_player_by_fd(client_fd, g_world)->name);
		g_world->groups->groups[g_world->groups->len] = &new_group;
		g_world->groups->len++;
		strcpy(result->message, "OK group=");
		strcat(result->message, test.message);
		strcat(result->message, "\n");
	}
	else
		strcpy(result->message, "ERR 429 TOO_MANY_REQUESTS\n");
}

static void	grp_invite(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	char	temp[12];

	if (get_group_by_player_fd(client_fd, g_world) == NULL)
		strcpy(result->message, "ERR 401 NOT_IN_GROUP\n");
	else if (get_player_by_name(test.message, g_world) == NULL
		|| !strcmp(test.message, "UNAUTHENTICATED"))
		strcpy(result->message, "ERR 404 PLAYER_NOT_FOUND\n");
	else
	{
		log_date();
		ft_printf("group invitation from %s to %s\n",
			get_player_by_fd(client_fd, g_world)->name, test.message);
		sprintf(temp, "%d", get_id_by_name(test.message, g_world));
		strcpy(result->message, "OK\n");
		result->players_0.len = 1;
		strcpy(result->players_0.ids[0], temp);
		strcpy(result->messages_0, "EVT GROUP INVITE ");
		strcat(result->messages_0, get_player_by_fd(client_fd, g_world)->name);
		strcat(result->messages_0, " ");
		strcat(result->messages_0, get_group_by_player_fd(client_fd,
				g_world)->name);
		strcat(result->messages_0, "\n");
	}
}

static void	grp_join(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	char	temp[12];

	sprintf(temp, "%d", client_fd);
	if (get_group_by_player_fd(client_fd, g_world) != NULL)
		strcpy(result->message, "ERR 402 ALREADY_IN_GROUP\n");
	else if (get_group_by_name(test.message, g_world) == NULL)
		strcpy(result->message, "ERR 404 GROUP_NOT_FOUND\n");
	else if (get_group_by_name(test.message,
			g_world)->players.len == MAX_LIST_LEN)
		strcpy(result->message, "ERR 429 TOO_MANY_REQUESTS\n");
	else
	{
		strcpy(result->message, "OK group=");
		strcat(result->message, test.message);
		strcat(result->message, "\n");
		log_date();
		ft_printf("adding %s to %s\n", get_player_by_fd(client_fd,
				g_world)->name, test.message);
		result->players_0 = get_group_by_name(test.message, g_world)->players;
		strcpy(result->messages_0, "EVT GROUP JOIN ");
		strcat(result->messages_0, get_player_by_fd(client_fd, g_world)->name);
		strcat(result->messages_0, "\n");
		append_in(temp, &(get_group_by_name(test.message, g_world)->players));
	}
}

static void	grp_leave(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	char	temp[12];

	sprintf(temp, "%d", client_fd);
	if (get_group_by_player_fd(client_fd, g_world) == NULL)
		strcpy(result->message, "ERR 401 NOT_IN_GROUP\n");
	else if (strcmp(test.message, get_group_by_player_fd(client_fd,
				g_world)->name))
		strcpy(result->message, "ERR 401 NOT_IN_GROUP\n");
	else if (get_group_by_name(test.message, g_world) == NULL)
		strcpy(result->message, "ERR 404 GROUP_NOT_FOUND\n");
	else
	{
		strcpy(result->message, "OK\n");
		log_date();
		ft_printf("removing %s to %s\n", get_player_by_fd(client_fd,
				g_world)->name, test.message);
		remove_from(temp, &(get_group_by_name(test.message, g_world)->players));
		result->players_0 = get_group_by_name(test.message, g_world)->players;
		strcpy(result->messages_0, "EVT GROUP LEAVE ");
		strcat(result->messages_0, get_player_by_fd(client_fd, g_world)->name);
		strcat(result->messages_0, "\n");
	}
}

int	cmd_group(t_command test, int client_fd, t_world *g_world, t_signal *result)
{
	if (!g_world || !result)
		return (0);
	if (test.type[5] == 'C')
		grp_create(test, client_fd, g_world, result);
	else if (test.type[5] == 'I')
		grp_invite(test, client_fd, g_world, result);
	else if (test.type[5] == 'J')
		grp_join(test, client_fd, g_world, result);
	else
		grp_leave(test, client_fd, g_world, result);
	return (1);
}
