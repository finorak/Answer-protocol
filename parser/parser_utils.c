/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:23:08 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 14:55:26 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/parser.h"
#include "../includes/data_extractor.h"
#include "../includes/cJSON.h"

size_t	get_buffer_size(const char *world_config_file)
{
	size_t	buffer_size;
	FILE	*fd;
	char	*curr_line;
	char	buffer[SIZE];

	fd = fopen(world_config_file, "rb");
	if (!fd)
		return (-1);
	buffer_size = 0;
	curr_line = fgets(buffer, SIZE, fd);
	while (curr_line)
	{
		buffer_size += strlen(curr_line);
		curr_line = fgets(buffer, SIZE, fd);
	}
	fclose(fd);
	return (buffer_size);
}

char	*get_buffer(const char *world_config_file, const size_t buffer_size)
{
	char	*buffer;
	int		fd;

	buffer = (char *)calloc(sizeof(char), buffer_size + 1);
	if (!buffer)
		return (NULL);
	fd = open(world_config_file, O_RDONLY);
	if (fd < 0)
	{
		free(buffer);
		return (NULL);
	}
	read(fd, buffer, buffer_size);
	buffer[buffer_size] = '\0';
	close(fd);
	return (buffer);
}

static bool	validate_other_data(cJSON *root, t_data *data)
{
	data->quests = extract_quests(root);
	if (!data->quests)
		return (
			cJSON_Delete(root),
			free_npcs(data->npcs, data->npcs->len), false);
	data->missions = extract_missions(root);
	if (!data->missions)
		return (
			cJSON_Delete(root),
			free_quests(data->quests, data->quests->len), false);
	data->dialogues = extract_dialogues(root);
	if (!data->dialogues)
		return (
			cJSON_Delete(root),
			free_missions(data->missions, data->missions->len), false);
	data->groups = extract_groups(root);
	if (!data->groups)
		return (
			cJSON_Delete(root),
			free_dialogues(data->dialogues, data->dialogues->len), false);
	cJSON_Delete(root);
	return (true);
}

// TODO: liverage this functon because it start to be full of shit.
bool	init_world_data(t_data *data, const char *buffer)
{
	cJSON	*root;

	if (!data)
		return (false);
	root = cJSON_Parse(buffer);
	if (!root)
		return (false);
	printf("her hkhlje\n");
	data->rooms = extract_rooms(root);
	if (!data->rooms)
		return (cJSON_Delete(root), NULL);
	data->items = extract_items(root);
	if (!data->items)
		return (
			cJSON_Delete(root),
			free_rooms(data->rooms, data->rooms->len), false);
	data->npcs = extract_npcs(root);
	if (!data->npcs)
		return (
			cJSON_Delete(root),
			free_items(data->items, data->items->len), false);
	return (validate_other_data(root, data));
}
