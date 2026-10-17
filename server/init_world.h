/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 06:45:25 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 09:58:57 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LIST_LEN 32
#define MAX_ID_LEN 32
#define MAX_NAME_LEN 32
#define MAX_DESCRIPTION_LEN 128
#define MAX_DIALOGUE_CONTENT_LEN 256
#define MAX_PLAYER 16
#define MAX_PLAYER_NAME 32
#define BUFFER_SIZE 1024

// list

typedef struct s_list_of
{
	char				ids[MAX_LIST_LEN][MAX_ID_LEN];
	int					len;
}						t_list_of;

// entity structures

typedef struct s_item
{
	char				id[MAX_ID_LEN];
	char				name[MAX_NAME_LEN];
	char				description[MAX_DESCRIPTION_LEN];
	int					obtainable;
	int					heal;
}						t_item;

typedef struct s_npc
{
	char				id[MAX_ID_LEN];
	char				name[MAX_NAME_LEN];
	char				description[MAX_DESCRIPTION_LEN];
	t_list_of			dialogues;
	int					dialogue_index;
	int					hp;
	int					attack;
	char				quest_id[MAX_ID_LEN];
}						t_npc;

typedef struct s_quest
{
	char				id[MAX_ID_LEN];
	char				name[MAX_NAME_LEN];
	char				description[MAX_DESCRIPTION_LEN];
	t_list_of			missions;
	int					done_missions;
	int					available;
	int					done;
	char				reward_id[MAX_ID_LEN];
	char				npc_owner_id[MAX_ID_LEN];
}						t_quest;

typedef struct s_mission
{
	char				id[MAX_ID_LEN];
	char				type[8];
	char				goal_id[MAX_ID_LEN];
}						t_mission;

typedef struct s_dialogue
{
	char				id[MAX_ID_LEN];
	char				content[MAX_DIALOGUE_CONTENT_LEN];
}						t_dialogue;

typedef struct s_group
{
	char				name[MAX_NAME_LEN];
	t_list_of			players;
}						t_group;

typedef struct s_room
{
	char				id[MAX_ID_LEN];
	char				name[MAX_NAME_LEN];
	char				description[MAX_DESCRIPTION_LEN];
	t_list_of			exits;
	t_list_of			npcs;
	t_list_of			items;
	t_list_of			players;
}						t_room;

// all entities

typedef struct s_all_items
{
	t_item				items[MAX_LIST_LEN];
	int					len;
}						t_all_items;

typedef struct s_all_npcs
{
	t_npc				npcs[MAX_LIST_LEN];
	int					len;
}						t_all_npcs;

typedef struct s_all_quests
{
	t_quest				quests[MAX_LIST_LEN];
	int					len;
}						t_all_quests;

typedef struct s_all_missions
{
	t_mission			missions[MAX_LIST_LEN];
	int					len;
}						t_all_missions;

typedef struct s_all_dialogues
{
	t_dialogue			dialogues[MAX_LIST_LEN];
	int					len;
}						t_all_dialogues;

typedef struct s_all_groups
{
	t_group				groups[MAX_LIST_LEN];
	int					len;
}						t_all_groups;

typedef struct s_all_rooms
{
	t_room				rooms[MAX_LIST_LEN];
	int					len;
}						t_all_rooms;

// players

typedef struct s_player
{
	int					fd;
	int					status;
	char				name[MAX_PLAYER_NAME];
	t_list_of			items;
	t_list_of			quests;
	int					hp;
	int					max_hp;
	int					attack;
	char				status_hp[16];
}						t_player;

typedef struct s_all_players
{
	t_player			players[MAX_PLAYER];
	int					len;
}						t_all_players;

// world structure

typedef struct s_world
{
	t_all_rooms			*rooms;
	t_all_items			*items;
	t_all_npcs			*npcs;
	t_all_quests		*quests;
	t_all_missions		*missions;
	t_all_dialogues		*dialogues;
	t_all_groups		*groups;
	t_all_players		*players;
}						t_world;

typedef struct s_command
{
	int					is_valid;
	char				type[32];
	char				message[128];
}						t_command;

typedef struct s_socket_property
{
	int					server_fd;
	struct sockaddr_in	address;
}						t_socket_property;

typedef struct s_signal
{
	t_list_of			players_0;
	char				messages_0[BUFFER_SIZE];
	t_list_of			players_1;
	char				messages_1[BUFFER_SIZE];
	char				message[BUFFER_SIZE];
}						t_signal;

void					initialize_world(t_world *world);
int						generate_weighted_attack(void);
