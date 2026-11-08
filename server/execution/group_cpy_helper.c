/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_cpy_heler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 09:31:56 by finorako          #+#    #+#             */
/*   Updated: 2026/10/24 09:33:00 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../../includes/world.h"

void	cpy(t_signal *result, t_command test)
{
	strcpy(result->message, "OK group=");
	strcat(result->message, test.message);
	strcat(result->message, "\n");
}
