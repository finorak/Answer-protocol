/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_helper_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 05:30:00 by finorako          #+#    #+#             */
/*   Updated: 2026/10/15 05:30:19 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	stack_size(t_stack *stack)
{
	int	counter;

	if (!stack)
		return (0);
	counter = 0;
	while (stack)
	{
		counter ++;
		stack = stack->next;
	}
	return (counter);
}
