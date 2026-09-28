/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 13:23:04 by finorako          #+#    #+#             */
/*   Updated: 2026/09/28 13:24:26 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "../includes/parser.h"

t_string_view	*new_string_view(char *string)
{
	t_string_view	*new_string;

	new_string = (t_string_view *)malloc(sizeof(t_string_view));
	if (!new_string || !string)
	{
		free(string);
		return (NULL);
	}
	strcpy(new_string->buffer, string);
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
