/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_extractor.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 10:22:05 by finorako          #+#    #+#             */
/*   Updated: 2026/10/18 14:04:52 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_EXTRACTOR_H
# define DATA_EXTRACTOR_H

# include "cJSON.h"
# include "world.h"
# include <stdbool.h>

# define ITEMS_KEY "items"
# define ROOM_KEY "world"
# define NPC_KEY "npcs"
# define QUEST_KEY "quests"
# define MISSION_KEY "missions"
# define GROUP_KEY "groups"

t_all_dialogues	*extract_dialogues(const cJSON *root, t_world *data);
t_all_missions	*extract_missions(const cJSON *root, t_world *data);
t_all_groups	*extract_groups(const cJSON *root, t_world *data);
t_all_quests	*extract_quests(const cJSON *root, t_world *data);
t_all_rooms		*extract_rooms(const cJSON *root, t_world *data);
t_all_items		*extract_items(const cJSON *root, t_world *data);
t_all_npcs		*extract_npcs(const cJSON *root, t_world *data);

bool			is_string(const cJSON *content);
bool			is_number(const cJSON *content);
bool			is_array(const cJSON *content);
bool			is_object(const cJSON *content);

#endif // !DATA_EXTRACTOR_H
