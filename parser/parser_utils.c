/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:23:08 by finorako          #+#    #+#             */
/*   Updated: 2026/09/28 16:55:32 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/parser.h"
#include "../includes/get_next_line.h"

static bool	get_lines(t_string_view **string_view, int fd)
{
	t_string_view	*head;
	char			*curr_line;

	if (!string_view)
		return (false);
	curr_line = get_next_line(fd);
	if (!curr_line)
	{
		free(*string_view);
		return (false);
	}
	head = *string_view;
	while (curr_line)
	{
		*string_view = get_last_string(*string_view);
		strcpy((*string_view)->buffer, curr_line);
		printf("%s", (*string_view)->buffer);
		(*string_view)->next = new_string_view();
		if (!(*string_view)->next)
		{
			free_string_view(*string_view);
			return (false);
		}
		free(curr_line);
		curr_line = get_next_line(fd);
	}
	*string_view = head;
	return (true);
}

bool	init_data(t_data *data, char *config)
{
	t_string_view	*string_view;
	int				fd;

	if (!data)
		return (false);
	string_view = new_string_view();
	if (!string_view)
		return (false);
	fd = open(config, O_RDONLY);
	get_lines(&string_view, fd);
	return (true);
}
