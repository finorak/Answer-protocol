/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:02:11 by finorako          #+#    #+#             */
/*   Updated: 2026/09/30 19:26:57 by finorako         ###   ########.fr       */
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
	cJSON	*heal;
	t_room	*room;
	int		index;
}				t_json_content;

size_t	get_buffer_size(char *world_config_file);
char	*get_buffer(char *world_config_file, size_t buffer_size);

// DATA initialization
bool	init_world_data(t_data *data, char *buffer);
t_room	*extract_room_from_key(char *key, cJSON *room_json, t_room *room);
t_item	*extract_item_from_key(char *key, cJSON *item_json, t_item *item);

// cjson helper
bool	traverse_room_array(
			cJSON *array, t_room *room, char *element_to_extract
			);

// ROOM EXTRACTOR
bool	traverse_room_object(cJSON *world_json, t_all_rooms *room_container);
bool	traverse_item_object(cJSON *world_json, t_all_items *item_container);

// Memory managment
void	free_rooms(t_all_rooms *rooms, int size);
void	free_data(t_data *data, char *buffer);
void	free_items(t_all_items *items, int size);
#endif
