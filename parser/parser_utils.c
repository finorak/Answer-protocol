/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:23:08 by finorako          #+#    #+#             */
/*   Updated: 2026/09/28 14:34:26 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../includes/parser.h"
#include "../includes/get_next_line.h"

static bool	get_lines(t_string_view *string, int fd)
{
	t_string_view	*head;
	char			*str;

	str = get_next_line(fd);
	if (!string || !str)
		return (false);
	head = string;
	while (str)
	{
		string = get_last_string(string);
		string->next = new_string_view(str);
		if (!string->next)
		{
			free_string_view(string);
			return (NULL);
		}
		free(str);
		str = get_next_line(fd);
	}
	return (true);
}

bool	init_data(t_data *data, char *config)
{
	int	fd;

	if (!data)
	{
		return (false);
	}
	data->lines = (t_string_view *)malloc(sizeof(t_string_view));
	if (!data->lines)
		return (false);
	fd = open(config, O_RDONLY);
	if (!get_lines(data->lines, fd))
		return (false);
	return (true);
}
