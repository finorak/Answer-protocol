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

bool	init_world_data(t_data *data, const char *buffer)
{
	cJSON	*root;

	if (!data)
		return (false);
	root = cJSON_Parse(buffer);
	if (!root)
		return (false);
	data->rooms = extract_rooms(root);
	data->items = extract_items(root);
	data->npcs = extract_npcs(root);
	data->quests = extract_quests(root);
	data->missions = extract_missions(root);
	data->dialogues = extract_dialogues(root);
	data->groups = extract_groups(root);
	cJSON_Delete(root);
	return (true);
}
