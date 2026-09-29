/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:23:04 by finorako          #+#    #+#             */
/*   Updated: 2026/09/28 16:55:43 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../includes/parser.h"

t_data	*new_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	return (data);
}

t_string_view	*new_string_view(void)
{
	t_string_view	*new_string;

	new_string = (t_string_view *)malloc(sizeof(t_string_view));
	if (!new_string)
	{
		return (NULL);
	}
	bzero(new_string->buffer, sizeof(new_string->buffer));
	new_string->len = 0;
	new_string->next = NULL;
	return (new_string);
}

t_string_view	*get_last_string(t_string_view *string)
{
	if (!string)
		return (NULL);
	while (string->next)
		string = string->next;
	return (string);
}
