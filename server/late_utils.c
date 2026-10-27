/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   late_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 07:36:49 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/27 07:37:21 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_utils.h"

void	recv_f(t_client cli, t_data *g_data)
{
	log_date();
	ft_printf("RECEIVED '%s' FROM PLAYER %d\n",
		cli.buf, player_id(cli.id, *(g_data->world)));
}
