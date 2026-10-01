/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_extractor.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 10:22:05 by finorako          #+#    #+#             */
/*   Updated: 2026/10/01 09:01:28 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_EXTRACTOR_H
# define DATA_EXTRACTOR_H

# include <stdlib.h>
# include <stdio.h>
# include "world.h"
# include "cJSON.h"

# define ITEMS_KEY "items"
# define ROOM_KEY "world"
# define NPC_KEY "npcs"
# define QUEST_KEY "quests"
# define MISSION_KEY "missions" 

t_all_dialogues	*extract_dialogues(cJSON *root);
t_all_missions	*extract_missions(cJSON *root);
t_all_quests	*extract_quests(cJSON *root);
t_all_rooms		*extract_rooms(cJSON *root);
t_all_items		*extract_items(cJSON *root);
t_all_npcs		*extract_npcs(cJSON *root);
t_all_groups	*extract_groups(cJSON *root);

#endif // !DATA_EXTRACTOR_H
