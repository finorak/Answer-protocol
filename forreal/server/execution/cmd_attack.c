/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_attack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 09:34:16 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/16 06:34:23 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main_utils.h"

int	cmd_attack(t_command test, int client_fd, t_world *g_world,
		t_signal *result)
{
	t_player *attacked;

	attacked = get_player_by_name(test.message, g_world);
	attacked.
	return (1);
}
