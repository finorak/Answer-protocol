/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interconnect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 12:57:23 by finorako          #+#    #+#             */
/*   Updated: 2026/10/13 09:21:28 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
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

static void	append_exits_to_last(t_stack **stack,
				t_room *curr_room, t_all_rooms *container)
{
	t_stack	*curr_stack;
	t_stack	*last;
	t_room	*room;
	int		index;

	if (!stack || !curr_room || !container)
		return ;
	index = 0;
	while (index < curr_room->exits.len)
	{
		room = get_room_from_id(container, curr_room->exits.ids[index]);
		if (!room)
		{
			index ++;
			continue ;
		}
		curr_stack = bfs_new_stack(room);
		last = get_last_stack(*stack);
		if (last)
			last->next = curr_stack;
		else
			*stack = curr_stack;
		index ++;
	}
}

// Iterating ovre the visited room, and see if the current
// one is inside, if yes, we return `true` overwise we return `false`
static bool	room_visited(t_stack	*current, t_stack *seen)
{
	char	*curr_key;
	char	*exits_key;

	if (!current || !seen)
		return (false);
	if (!seen->data)
		return (false);
	curr_key = (char *)((t_room *)current->data)->id;
	while (seen)
	{
		exits_key = (char *)((t_room *)seen->data)->id;
		if (strcmp(curr_key, exits_key) == 0)
			return (true);
		seen = seen->next;
	}
	return (false);
}

bool	room_interconnect(t_stack **stack,
			t_all_rooms *container, char **room_ids, int *counter)
{
	t_stack	*seen;
	t_stack	*curr;

	if (!room_ids)
		return (false);
	if (!stack)
		return (stack_free(*stack), false);
	seen = bfs_new_stack(NULL);
	if (!seen)
		return (stack_free(*stack), false);
	while (*stack)
	{
		curr = pop_first(stack);
		if (room_visited(curr, seen))
		{
			printf("%s\n", ((t_room *)curr->data)->id);
			*counter += 1;
			continue ;
		}
		stack_append(&seen, curr);
		append_exits_to_last(stack, (t_room *)curr->data, container);
	}
	stack_free(seen);
	stack_free(*stack);
	return (*counter >= INTERCONNECTION_BASE_COUNT);
}
