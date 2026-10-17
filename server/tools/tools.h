/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:29:35 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 20:04:32 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world.h"

void		mess(t_world *world);
void		add_player(int client_fd, t_world *world);
void		remove_player(int client_fd, t_world *world);

int			in(char *element, t_list_of list);
void		remove_from(char *element, t_list_of *list);
void		append_in(char *element, t_list_of *list);
void		merge(t_list_of *by, t_list_of *from);
void		concat_into_message(char *message, t_list_of list, int player,
				t_world *world);

int			get_id_by_name(char *name, t_world *world);
t_player	*get_player_by_fd(int client_fd, t_world *world);
t_player	*get_player_by_item(char *item_id, t_world *world);
t_player	*get_player_by_name(char *name, t_world *world);

t_room		*get_room_by_id(char *room_id, t_world *world);
t_room		*get_room_by_player_fd(int client_fd, t_world *world);
t_room		*get_room_by_item_id(char *item_id, t_world *world);
t_room		*get_room_by_npc_id(char *npc_id, t_world *world);

t_group		*get_group_by_name(char *name, t_world *world);
t_group		*get_group_by_player_name(char *player_name, t_world *world);
t_group		*get_group_by_player_fd(int id, t_world *world);

t_item		*get_item_by_id(char *id, t_world *world);
t_npc		*get_npc_by_id(char *id, t_world *world);
t_quest		*get_quest_by_id(char *id, t_world *world);
t_mission	*get_mission_by_id(char *id, t_world *world);
t_dialogue	*get_dialogue_by_id(char *id, t_world *world);
