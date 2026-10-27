/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_attack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:34:16 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/27 09:30:46 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"
#include <stdio.h>
#include <string.h>

static int	consequence(t_player *player, int client_fd, t_signal *result,
	t_world *g_world)
{
	char name[MAX_NAME_LEN];

	if (player->hp <= player->max_hp / 2)
		strcpy(player->status_hp, "unhealthy");
	if (player->hp == 0)
	{
		strcpy(result->message, "OK {\"message\": \"You got smoked\"}\n");
		strcpy(name, player->name);
		remove_player(client_fd, g_world);
		add_player(client_fd, g_world);
		strcpy(player->name, name);
		return (1);
	}
	return (0);
}

static int	attack(t_npc *attacked, int client_fd, t_world *g_world,
		t_signal *result)
{
	int	damage;
	int	attacker_damage;

	damage = 3 * get_player_by_fd(client_fd, g_world)->attack
		+ generate_weighted_attack();
	attacker_damage = attacked->attack;
	get_player_by_fd(client_fd, g_world)->hp -= attacker_damage;
	attacked->hp -= damage;
	if (attacked->hp < 0)
		attacked->hp = 0;
	if (get_player_by_fd(client_fd, g_world)->hp < 0)
		get_player_by_fd(client_fd, g_world)->hp = 0;
	if (consequence(get_player_by_fd(client_fd, g_world), client_fd,
			result, g_world))
		return (1);
	log_date();
	ft_printf("%s attacked %s (-%d for damage=%d)\n",
		get_player_by_fd(client_fd, g_world)->name, attacked->id,
		attacker_damage, damage);
	strcpy(result->message, "OK {\"attacker_hp\" : ");
	strcat_number(result->message, get_player_by_fd(client_fd, g_world)->hp);
	strcat(result->message, ", \"target_hp\" : ");
	strcat_number(result->message, attacked->hp);
	strcat(result->message, ", \"damage\" : ");
	return (strcat_number(result->message, damage), 0);
}

int	cmd_attack(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	t_npc	*attacked;

	if (!g_world || !result)
		return (0);
	attacked = get_npc_by_id(test.message, g_world);
	if (!attacked || !in(attacked->id, get_room_by_player_fd(client_fd,
				g_world)->npcs))
		strcpy(result->message, "ERR 404 NPC_NOT_FOUND\n");
	else if (attacked->hp == -1)
		strcpy(result->message, "ERR 405 NPC_NOT_HOSTILE\n");
	else if (attacked->hp == 0)
	{
		strcpy(result->message, "OK {");
		strcat_double_quoted(result->message, attacked->id);
		strcat(result->message, ": \"dead\"}\n");
	}
	else
	{
		if (!attack(attacked, client_fd, g_world, result))
			strcat(result->message, ", \"status\" : \"combat\"}\n");
	}
	return (1);
}
