/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 06:28:34 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 20:04:52 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "../main_utils.h"

int	in(char *element, t_list_of list)
{
	int	i;

	if (!element)
		return (0);
	i = -1;
	while (++i < list.len)
	{
		if (!strcmp(list.ids[i], element))
			return (1);
	}
	return (0);
}

void	remove_from(char *element, t_list_of *list)
{
	int	i;
	int	j;

	if (!element || !list)
		return ;
	i = 0;
	while (i < list->len)
	{
		if (!strcmp(list->ids[i], element))
		{
			j = i;
			while (j < list->len - 1)
			{
				strcpy(list->ids[j], list->ids[j + 1]);
				j++;
			}
			list->len--;
			break ;
		}
		i++;
	}
}

void	append_in(char *element, t_list_of *list)
{
	if (!element || !list)
		return ;
	if (list->len < MAX_LIST_LEN)
	{
		strcpy(list->ids[list->len], element);
		list->len++;
	}
}

void	merge(t_list_of *by, t_list_of *from)
{
	int	i;

	if (!by || !from)
		return ;
	i = 0;
	while (i < by->len)
	{
		append_in(by->ids[i], from);
		i++;
	}
	by->len = 0;
}

void	concat_into_message(char *message, t_list_of list, int player,
		t_world *world)
{
	int	i;

	if (!message || !world)
		return ;
	i = 0;
	strcat(message, "[");
	while (i < list.len)
	{
		if (i != 0)
			strcat(message, ", ");
		if (player && strcmp(list.ids[i], "-1"))
			strcat_double_quoted(message, get_player_by_fd(atoi(list.ids[i]),
					world)->name);
		else
			strcat_double_quoted(message, list.ids[i]);
		i++;
	}
	strcat(message, "]");
}
