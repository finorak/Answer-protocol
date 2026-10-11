/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:02:11 by finorako          #+#    #+#             */
/*   Updated: 2026/10/10 17:49:25 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#ifndef SIZE
#define SIZE 1024
#endif

#include "../includes/cJSON.h"
#include "../includes/world.h"
#include <stdbool.h>
#include <stddef.h>

#define ROOM_DIRETCION 4

// MIGHT REMOVE THIS LATER ON AS
// IT'S LIKE A WAST.
typedef struct s_buffer_store {
  size_t buffer_size;
  char *buffer;
} t_buffer_store;

// USED SO THAT THE DATA TYPE CHECK BECOME MORE
// PORTABLE WIHOUT CREATING A SINGLE FUCTION
// FOR EACH DATA TYPE.
typedef enum e_data_type {
  TYPE_NPC,
  TYPE_ROOM,
  TYPE_QUEST,
  TYPE_MISSION,
  TYPE_ITEM,
  TYPE_DIALOG,
  TYPE_GROUP,
  TYPE_STRING_TABLE
} t_data_type;

// JSON DATA PARSER
size_t get_buffer_size(const char *world_config_file);
char *get_buffer(const char *world_config_file, size_t buffer_size);

// DATA INITIALIZATION
t_mission *extract_mission_from_key(const char *key, const cJSON *npc_json,
                                    t_mission *mission);
t_quest *extract_quest_from_key(const char *key, const cJSON *quest_json,
                                t_quest *quest);
t_room *extract_room_from_key(const char *key, const cJSON *room_json,
                              t_room *room);
t_item *extract_item_from_key(const char *key, const cJSON *item_json,
                              t_item *item);
t_npc *extract_npc_from_key(const char *key, const cJSON *npc_json, t_npc *npc);
t_group *extract_goup_from_key(const char *key, cJSON *group_json,
                               t_npc *group);
t_dialogue *extract_dialogues_from_key(const char *key, cJSON *dialogue_json,
                                       t_dialogue *dialogue);
bool init_world_data(t_data *data, const char *buffer);

// DATA VALIDATOR
bool data_validator(t_data *data);
char *extract_room_id(char *room_id);
bool key_is_reconnecting(char *curr_id, t_list_of exits);

// CJSON ARRAY HELPER
bool traverse_npc_array(const cJSON *array, t_npc *room);
bool traverse_quest_array(const cJSON *array, t_quest *quest);
bool traverse_room_array(const cJSON *array, t_room *room,
                         const char *element_to_extract);

// CJSON OBJECT HELPER
bool traverse_room_object(const cJSON *world_json, t_all_rooms *room_container);
bool traverse_item_object(const cJSON *world_json, t_all_items *item_container);
bool traverse_npc_object(const cJSON *world_json, t_all_npcs *npc_container);
bool traverse_quest_object(const cJSON *world_json,
                           t_all_quests *quest_container);
bool traverse_mission_object(const cJSON *mission_json,
                             t_all_missions *mission_container);

// MEMORY MANAGMENT
// TODO: update the bellow function to use
// the enum e_data_type so that it is less
// redundant.
void free_data(t_data *data, char *buffer);
void custom_free(void *data, int size, t_data_type data_type);

// FREE TEST UNCTION

#endif
