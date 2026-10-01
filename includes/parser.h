/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:02:11 by finorako          #+#    #+#             */
/*   Updated: 2026/10/01 08:58:38 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# ifndef SIZE
#  define SIZE 1024
# endif

# include <stdbool.h>
# include <stddef.h>
# include "../includes/cJSON.h"
# include "../includes/world.h"

typedef struct s_buffer_store
{
	size_t		buffer_size;
	char		*buffer;
}				t_buffer_store;

typedef struct s_json_content
{
	cJSON	*desc;
	cJSON	*name;
	cJSON	*exits;
	cJSON	*npcs;
	cJSON	*items;
	cJSON	*obtainable;
	cJSON	*dialogues;
	cJSON	*heal;
	cJSON	*hp;
	cJSON	*attack;
	cJSON	*quest_id;
	cJSON	*missions;
	cJSON	*reward;
	cJSON	*npc_owner;
	cJSON	*type;
	cJSON	*goal;
	int		index;
}				t_json_content;

// JSON DATA PARSER
size_t		get_buffer_size(char *world_config_file);
char		*get_buffer(char *world_config_file, size_t buffer_size);

// DATA INITIALIZATION
t_mission	*extract_mission_from_key(const char *key, cJSON *npc_json,
				t_mission *mission);
t_quest		*extract_quest_from_key(const char *key, cJSON *quest_json,
				t_quest *quest);
t_room		*extract_room_from_key(const char *key, cJSON *room_json,
				t_room *room);
t_item		*extract_item_from_key(const char *key, cJSON *item_json,
				t_item *item);
t_npc		*extract_npc_from_key(const char *key, cJSON *npc_json, t_npc *npc);
t_group		*extract_goup_from_key(
				const char *key, cJSON *group_json, t_npc *group);
t_dialogue	*extract_dialogues_from_key(
				const char *key, cJSON *dialogue_json, t_dialogue *dialogue);
bool		init_world_data(t_data *data, const char *buffer);

// cjson array helper
bool		traverse_npc_array(cJSON *array, t_npc *room);
bool		traverse_quest_array(cJSON *array, t_quest *quest);
bool		traverse_room_array(cJSON *array, t_room *room,
				char *element_to_extract);

// cjson object helper
bool		traverse_room_object(cJSON *world_json,
				t_all_rooms *room_container);
bool		traverse_item_object(cJSON *world_json,
				t_all_items *item_container);
bool		traverse_npc_object(cJSON *world_json, t_all_npcs *npc_container);
bool		traverse_quest_object(cJSON *world_json,
				t_all_quests *quest_container);
bool		traverse_mission_object(cJSON *mission_json,
				t_all_missions *mission_container);

// Memory MANAGMENT
void		free_rooms(t_all_rooms *rooms, int size);
void		free_data(t_data *data, char *buffer);
void		free_items(t_all_items *items, int size);
#endif
