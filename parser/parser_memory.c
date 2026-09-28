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

#include <stdlib.h>
#include "../includes/parser.h"

void	free_string_view(t_string_view *string)
{
	t_string_view	*tmp;

	if (!string)
		return ;
	while (string)
	{
		tmp = string;
		free(string);
		string = tmp->next;
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_string_view(data->lines);
	free(data);
}
