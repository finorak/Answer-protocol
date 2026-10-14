/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:23:08 by finorako          #+#    #+#             */
/*   Updated: 2026/10/14 09:09:49 by megalonia        ###   ########.fr       */
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

// Given a file, we try to get the actual size
// of that file so that we don't use a static
// value.
// TODO: Remove this function and use the getline
// function.
size_t	get_buffer_size(const char *world_config_file)
{
	size_t	buffer_size;
	FILE	*fd;
	char	*curr_line;
	char	buffer[1024];

	fd = fopen(world_config_file, "rb");
	if (!fd)
		return (-1);
	buffer_size = 0;
	curr_line = fgets(buffer, 1024, fd);
	while (curr_line)
	{
		buffer_size += strlen(curr_line);
		curr_line = fgets(buffer, 1024, fd);
	}
	fclose(fd);
	return (buffer_size);
}

// TODO: might replace this because why the fuk
// did I do this. getline will be the function to
// replace this.
char	*get_buffer(const char *world_config_file, const size_t buffer_size)
{
	char	*buffer;
	int		fd;

	buffer = (char *)calloc(buffer_size + 1, sizeof(char));
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
	{
		fprintf(stderr, "Map is invalid\n");
		return (false);
	}
	data->rooms = extract_rooms(root, data);
	data->items = extract_items(root, data);
	data->npcs = extract_npcs(root, data);
	data->quests = extract_quests(root, data);
	data->missions = extract_missions(root, data);
	data->dialogues = extract_dialogues(root, data);
	data->groups = extract_groups(root, data);
	cJSON_Delete(root);
	if (!data->extract)
	{
		fprintf(stderr, "An error occured during parsing\n");
		return (false);
	}
	return (data_validator(data));
}
