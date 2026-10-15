/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interconnect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 12:57:23 by finorako          #+#    #+#             */
/*   Updated: 2026/10/15 05:34:57 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>
#include "../../includes/parser.h"

// TODO: Fix error in this funciton, but still can't find what the
// error is.
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
		room = get_room_from_id(container, curr_room->exits.ids[index++]);
		if (!room)
			continue ;
		curr_stack = new_stack(room);
		last = get_last_stack(*stack);
		if (last)
			last->next = curr_stack;
		else
			*stack = curr_stack;
	}
}

// Iterating ovre the visited stack, and see if the current
// one is inside, if yes, we return `true` overwise we return `false`
static bool	room_visited(t_stack *current, t_stack *seen)
{
	char	*curr_room_key;
	char	*neighboor_key;

	if (!current || !seen)
		return (false);
	if (!seen->data)
		return (false);
	curr_room_key = (char *)((t_room *)current->data)->id;
	while (seen)
	{
		neighboor_key = (char *)((t_room *)seen->data)->id;
		if (strcmp(curr_room_key, neighboor_key) == 0)
			return (true);
		seen = seen->next;
	}
	return (false);
}

// Given a map, we iterate through all the
// rooms and their exits: doing a simple
// bfs and count the number of time we
// visite a room, based on that count
// we can assume that if it's > than
// the `INTERCONNECTION_BASE_COUNT` the room do
// intersect.
bool	interconnection_checker(t_stack **stack,
			t_all_rooms *container, char **room_ids, int *counter)
{
	t_stack	*visited;
	t_stack	*curr;

	if (!stack)
		return (stack_free(*stack), false);
	if (!room_ids)
		return (false);
	visited = NULL;
	if (!stack || !room_ids)
		return (stack_free(*stack), false);
	while (*stack)
	{
		curr = pop_first(stack);
		if (room_visited(curr, visited))
		{
			*counter += 1;
			continue ;
		}
		stack_append(&visited, curr);
		append_exits_to_last(stack, (t_room *)curr->data, container);
	}
	stack_free(visited);
	stack_free(*stack);
	return (*counter >= INTERCONNECTION_BASE_COUNT);
}
