/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:23:08 by finorako          #+#    #+#             */
/*   Updated: 2026/10/20 08:37:54 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/parser.h"
#include "../includes/data_extractor.h"
#include "../includes/cJSON.h"

// distribution:
// p   : min-max
// 0.30: 001-005
// 0.25: 006-010
// 0.20: 011-014
// 0.15: 015-017
// 0.10: 018-020
int	generate_weighted_attack(void)
{
	int	r;
	int	attack;

	srand(time(NULL));
	r = rand() % 100;
	if (r < 30)
		attack = 1 + (rand() % 5);
	else if (r < 55)
		attack = 6 + (rand() % 5);
	else if (r < 75)
		attack = 11 + (rand() % 4);
	else if (r < 90)
		attack = 15 + (rand() % 3);
	else
		attack = 18 + (rand() % 3);
	return (attack);
}

static void	initialize_client_manager(t_all_players *players)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		players->players[i].fd = -1;
		players->players[i].status = 0;
		strcpy(players->players[i].name, "UNAUTHENTICATED");
		players->players[i].items.len = 0;
		players->players[i].quests.len = 0;
		players->players[i].hp = MAX_PLAYER_HP;
		players->players[i].max_hp = MAX_PLAYER_HP;
		players->players[i].attack = generate_weighted_attack();
		strcpy(players->players[i].status_hp, "healthy");
		i++;
	}
	players->len = 0;
}

static void	get_data(t_world *data, cJSON *root)
{
	if (!data || !root)
		return ;
	data->rooms = extract_rooms(root, data);
	data->items = extract_items(root, data);
	data->npcs = extract_npcs(root, data);
	data->quests = extract_quests(root, data);
	data->missions = extract_missions(root, data);
	data->dialogues = extract_dialogues(root, data);
	data->groups = extract_groups(root, data);
	data->players = NULL;
	if (!data->extract)
		return ;
	data->players = (t_all_players *)calloc(MAX_PLAYER, sizeof(t_all_players));
	if (!data->players)
	{
		data->extract = false;
		return ;
	}
	initialize_client_manager(data->players);
}

bool	init_world_data(t_world *data, const char *buffer)
{
	cJSON	*root;

	if (!data)
		return (fprintf(stdout, "Error\n"), false);
	root = cJSON_Parse(buffer);
	if (!root)
		return (fprintf(stderr, "Map is invalid\n"), false);
	data->extract = true;
	get_data(data, root);
	cJSON_Delete(root);
	if (!data->extract)
	{
		fprintf(
			stderr,
			"An error occured during parsing. Possibly \
due to a key missing or value invalid.\n");
		return (false);
	}
	return (data_validator(data));
}
