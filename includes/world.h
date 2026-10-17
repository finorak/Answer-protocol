/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 15:09:51 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/16 18:01:09 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include <stdbool.h>
# define BUFFER_SIZE 1024

# define MAX_LIST_LEN 32
# define MAX_ID_LEN 32
# define MAX_NAME_LEN 32
# define MAX_DESCRIPTION_LEN 128
# define MAX_DIALOGUE_CONTENT_LEN 256
# define MAX_PLAYER 16

typedef struct s_list_of
{
	char	ids[MAX_LIST_LEN][MAX_ID_LEN];
	int		len;
}				t_list_of;

typedef struct s_item
{
	char	id[MAX_ID_LEN];
	char	name[MAX_NAME_LEN];
	char	description[MAX_DESCRIPTION_LEN];
	int		obtainable;
	int		heal;
}				t_item;

typedef struct npc
{
	t_list_of	dialogues;
	char		id[MAX_ID_LEN];
	char		name[MAX_NAME_LEN];
	char		description[MAX_DESCRIPTION_LEN];
	int			dialogue_index;
	int			hp;
	int			attack;
	char		quest_id[BUFFER_SIZE];
}			t_npc;

typedef struct quest
{
	t_list_of	missions;
	char		id[MAX_ID_LEN];
	char		name[MAX_NAME_LEN];
	char		description[MAX_DESCRIPTION_LEN];
	int			done_missions;
	int			available;
	int			done;
	char		reward_id[MAX_ID_LEN];
	char		npc_owner_id[MAX_ID_LEN];
}				t_quest;

typedef struct mission
{
	char	id[MAX_ID_LEN];
	char	type[MAX_ID_LEN];
	char	goal_id[MAX_ID_LEN];
}				t_mission;

typedef struct dialogue
{
	char	content[BUFFER_SIZE];
	char	id[MAX_ID_LEN];
}			t_dialogue;

typedef struct group
{
	t_list_of	players;
	char		name[MAX_NAME_LEN];
}				t_group;

typedef struct room
{
	t_list_of	exits;
	t_list_of	npcs;
	t_list_of	items;
	t_list_of	players;
	char		description[MAX_DESCRIPTION_LEN];
	char		name[MAX_NAME_LEN];
	char		id[MAX_ID_LEN];
}				t_room;

typedef struct s_player
{
	t_list_of	items;
	t_list_of	quests;
	char		status_hp[MAX_ID_LEN];
	char		name[MAX_NAME_LEN];
	int			status;
	int			max_hp;
	int			attack;
	int			fd;
	int			hp;
}				t_player;

typedef struct s_all_players
{
	t_player	players[MAX_PLAYER];
	int			len;
}				t_all_players;

typedef struct all_items
{
	t_item	*items[MAX_ID_LEN];
	int		len;
}				t_all_items;

typedef struct all_npcs
{
	t_npc	*npcs[MAX_ID_LEN];
	int		len;
}				t_all_npcs;

typedef struct all_quests
{
	t_quest	*quests[MAX_ID_LEN];
	int		len;
}				t_all_quests;

typedef struct all_missions
{
	t_mission	*missions[MAX_ID_LEN];
	int			len;
}				t_all_missions;

typedef struct all_dialogues
{
	t_dialogue	*dialogues[MAX_ID_LEN];
	int			len;
}				t_all_dialogues;

typedef struct all_groups
{
	t_group	*groups[MAX_ID_LEN];
	int		len;
}				t_all_groups;

typedef struct all_rooms
{
	t_room	*rooms[MAX_ID_LEN];
	int		len;
}				t_all_rooms;

// Store the data inside this struct
// for a better manipulation.
typedef struct s_data
{
	t_all_dialogues	*dialogues;
	t_all_missions	*missions;
	t_all_players	*players;
	t_all_groups	*groups;
	t_all_quests	*quests;
	t_all_rooms		*rooms;
	t_all_items		*items;
	t_all_npcs		*npcs;
	bool			extract;
	bool			freed;
}				t_data;

#endif // !WORLD_H
