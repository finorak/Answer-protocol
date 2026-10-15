/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:02:11 by finorako          #+#    #+#             */
/*   Updated: 2026/10/13 09:03:08 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/cJSON.h"
# include "../includes/world.h"
# include <stdbool.h>
# include <stddef.h>
# define SIZE 1024
// TODO: THE VALUE SHOULD BE WAY MORE FLEXIBLE
// COUNT >= 4 SHOULD STILL WORK
# define INTERCONNECTION_BASE_COUNT 4

# include "../includes/cJSON.h"
# include "../includes/world.h"
# include <stdbool.h>
# include <stddef.h>

# define ROOM_DIRETCION 4

// MIGHT REMOVE THIS LATER ON AS
// IT'S LIKE A WAST.
typedef struct s_buffer_store
{
	size_t			buffer_size;
	char			*buffer;
}					t_buffer_store;

// USED SO THAT THE DATA TYPE CHECK BECOME MORE
// PORTABLE WIHOUT CREATING A SINGLE FUCTION
// FOR EACH DATA TYPE.
typedef enum e_data_type
{
	TYPE_STRING_TABLE,
	TYPE_MISSION,
	TYPE_DIALOG,
	TYPE_QUEST,
	TYPE_GROUP,
	TYPE_ROOM,
	TYPE_ITEM,
	TYPE_NPC
}				t_data_type;

typedef struct s_stack
{
	struct s_stack	*next;
	void			*data;
	int				counter;
}					t_stack;

// JSON DATA PARSER
size_t				get_buffer_size(const char *world_config_file);
char				*get_buffer(const char *world_config_file,
						size_t buffer_size);

// DATA INITIALIZATION
t_mission			*extract_mission_from_key(const char *key,
						const cJSON *npc_json, t_mission *mission);
t_quest				*extract_quest_from_key(const char *key,
						const cJSON *quest_json, t_quest *quest);
t_room				*extract_room_from_key(const char *key,
						const cJSON *room_json, t_room *room);
t_item				*extract_item_from_key(const char *key,
						const cJSON *item_json, t_item *item);
t_npc				*extract_npc_from_key(const char *key,
						const cJSON *npc_json, t_npc *npc);
t_group				*extract_goup_from_key(const char *key, cJSON *group_json,
						t_npc *group);
t_dialogue			*extract_dialogues_from_key(const char *key,
						cJSON *dialogue_json, t_dialogue *dialogue);
bool				init_world_data(t_data *data, const char *buffer);

// DATA VALIDATOR
bool				data_validator(t_data *data);
char				*extract_room_id(char *room_id);

// BFS UTILITIES
t_stack				*stack_append(t_stack **current_stack, t_stack *new_el);
t_stack				*pop_first(t_stack **stack);
t_stack				*get_last_stack(t_stack *stack);
t_stack				*new_stack(void *data);
void				stack_free(t_stack *stack);

// CJSON ARRAY HELPER
bool				traverse_npc_array(const cJSON *array, t_npc *room);
bool				traverse_quest_array(const cJSON *array, t_quest *quest);
bool				traverse_room_array(const cJSON *array, t_room *room,
						const char *element_to_extract);

// CJSON OBJECT HELPER
bool				traverse_room_object(const cJSON *world_json,
						t_all_rooms *room_container);
bool				traverse_item_object(const cJSON *world_json,
						t_all_items *item_container);
bool				traverse_npc_object(const cJSON *world_json,
						t_all_npcs *npc_container);
bool				traverse_quest_object(const cJSON *world_json,
						t_all_quests *quest_container);
bool				traverse_mission_object(const cJSON *mission_json,
						t_all_missions *mission_container);

// DATA INITIALIZATION
t_mission			*extract_mission_from_key(const char *key,
						const cJSON *npc_json, t_mission *mission);
t_quest				*extract_quest_from_key(const char *key,
						const cJSON *quest_json, t_quest *quest);
t_room				*extract_room_from_key(const char *key,
						const cJSON *room_json, t_room *room);
t_item				*extract_item_from_key(const char *key,
						const cJSON *item_json, t_item *item);
t_npc				*extract_npc_from_key(const char *key,
						const cJSON *npc_json, t_npc *npc);
t_group				*extract_goup_from_key(const char *key, cJSON *group_json,
						t_npc *group);
t_dialogue			*extract_dialogues_from_key(const char *key,
						cJSON *dialogue_json, t_dialogue *dialogue);
bool				init_world_data(t_data *data, const char *buffer);

// INTERCONECTION
t_room				*get_room_from_id(t_all_rooms *container, char *id);
bool				room_interconnect(t_stack **stack, t_all_rooms *container,
						char **room_ids, int *counter);

// CJSON ARRAY HELPER
bool				traverse_npc_array(const cJSON *array, t_npc *room);
bool				traverse_quest_array(const cJSON *array, t_quest *quest);
bool				traverse_room_array(const cJSON *array, t_room *room,
						const char *element_to_extract);

// CJSON OBJECT HELPER
bool				traverse_room_object(const cJSON *world_json,
						t_all_rooms *room_container);
bool				traverse_item_object(const cJSON *world_json,
						t_all_items *item_container);
bool				traverse_npc_object(const cJSON *world_json,
						t_all_npcs *npc_container);
bool				traverse_quest_object(const cJSON *world_json,
						t_all_quests *quest_container);
bool				traverse_mission_object(const cJSON *mission_json,
						t_all_missions *mission_container);

// MEMORY MANAGMENT
void				free_data(t_data *data, char *buffer);
void				custom_free(void *data, int size, t_data_type data_type);

#endif
