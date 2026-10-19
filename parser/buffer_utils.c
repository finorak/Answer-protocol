/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megalonia </var/spool/mail/megalonia>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 19:18:07 by megalonia         #+#    #+#             */
/*   Updated: 2026/10/17 19:18:58 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

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

	if (buffer_size <= 10)
		return (NULL);
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
