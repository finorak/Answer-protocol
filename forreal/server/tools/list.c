/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 06:28:34 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/12 06:35:21 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

int	in(char *element, t_list_of list)
{
	int	i;

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
	if (list->len < MAX_LIST_LEN)
	{
		strcpy(list->ids[list->len], element);
		list->len++;
	}
}
