/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:34:37 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/15 10:34:50 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_utils.h"

t_signal	val_exec(int client_fd, char *buf, t_world *world)
{
	t_signal	sign;
	t_command	test;

	test = validation_1(buf);
	if (test.is_valid == 0)
	{
		strcpy(sign.message, test.message);
		sign.players_0.len = 0;
		sign.players_1.len = 0;
		return (sign);
	}
	else
	{
		test = validation_2(test);
		if (test.is_valid == 0)
		{
			strcpy(sign.message, test.message);
			sign.players_0.len = 0;
			sign.players_1.len = 0;
			return (sign);
		}
		else
			return (execution(test, client_fd, world));
	}
}
