/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:02:11 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 15:31:30 by finorako         ###   ########.fr       */
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

# define ROOM_DIRETCION 4

typedef struct s_buffer_store
{
	size_t		buffer_size;
	char		*buffer;
}				t_buffer_store;

// JSON DATA PARSER
size_t		get_buffer_size(const char *world_config_file);
char		*get_buffer(const char *world_config_file, size_t buffer_size);

// DATA INITIALIZATION
t_mission	*extract_mission_from_key(const char *key, const cJSON *npc_json,
				t_mission *mission);
t_quest		*extract_quest_from_key(const char *key, const cJSON *quest_json,
				t_quest *quest);
t_room		*extract_room_from_key(const char *key, const cJSON *room_json,
				t_room *room);
t_item		*extract_item_from_key(const char *key, const cJSON *item_json,
				t_item *item);
t_npc		*extract_npc_from_key(
				const char *key, const cJSON *npc_json, t_npc *npc);
t_group		*extract_goup_from_key(
				const char *key, cJSON *group_json, t_npc *group);
t_dialogue	*extract_dialogues_from_key(
				const char *key, cJSON *dialogue_json, t_dialogue *dialogue);
bool		init_world_data(t_data *data, const char *buffer);

// cjson array helper
bool		traverse_npc_array(const cJSON *array, t_npc *room);
bool		traverse_quest_array(
				const cJSON *array, t_quest *quest);
bool		traverse_room_array(const cJSON *array, t_room *room,
				const char *element_to_extract);

// cjson object helper
bool		traverse_room_object(const cJSON *world_json,
				t_all_rooms *room_container);
bool		traverse_item_object(const cJSON *world_json,
				t_all_items *item_container);
bool		traverse_npc_object(
				const cJSON *world_json, t_all_npcs *npc_container);
bool		traverse_quest_object(const cJSON *world_json,
				t_all_quests *quest_container);
bool		traverse_mission_object(const cJSON *mission_json,
				t_all_missions *mission_container);

// Memory MANAGMENT
void		free_data(t_data *data, char *buffer);
void		free_rooms(t_all_rooms *rooms, int size);
void		free_items(t_all_items *items, int size);
void		free_missions(t_all_missions *items, int size);
void		free_quests(t_all_quests *items, int size);
void		free_npcs(t_all_npcs *items, int size);
void		free_groups(t_all_groups *groups, int size);
void		free_dialogues(t_all_dialogues *items, int size);
#endif
