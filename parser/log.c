/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:10:45 by finorako          #+#    #+#             */
/*   Updated: 2026/09/28 16:13:50 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/parser.h"

void	print_log(t_data *data)
{
	t_string_view	*tmp;

	if (!data)
		return ;
	while (data->lines)
	{
		tmp = data->lines;
		printf("%s", data->lines->buffer);
		free(data->lines);
		data->lines = tmp->next;
	}
	free(data);
}
