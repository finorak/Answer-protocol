/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 14:25:05 by finorako          #+#    #+#             */
/*   Updated: 2026/09/28 14:26:21 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../includes/parser.h"

void	free_string_view(t_string_view *string)
{
	t_string_view	*tmp;

	if (!string)
	{
		return ;
	}
	while (string)
	{
		tmp = string;
		free(string);
		string = tmp->next;
	}
}

void	free_last_node(t_string_view *string_view)
{
	t_string_view	*last;

	if (!string_view)
		return ;
	last = get_last_string(string_view);
	if (!last || !last->buffer[0])
		return ;
	free(last);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_string_view(data->lines);
	free(data);
}
