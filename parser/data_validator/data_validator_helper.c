/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validator_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako  </var/spool/mail/finorako>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 17:30:47 by finorako          #+#    #+#             */
/*   Updated: 2026/10/13 08:58:29 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/parser.h"

/*
* Extracting ids so that we can just verify
* the interconection of the rooms
*/
char	*extract_room_id(char *room_id)
{
	char	*string;
	int		size;

	if (!room_id)
		return (NULL);
	size = strlen(room_id);
	string = (char *)calloc(size + 1, sizeof(char));
	if (!string)
		return (NULL);
	strncpy(string, room_id, size);
	return (string);
}
