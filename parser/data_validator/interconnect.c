/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interconnect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 12:57:23 by finorako          #+#    #+#             */
/*   Updated: 2026/10/16 18:00:42 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>
#include "../../includes/parser.h"

// Prototype for preprocessing
static bool	room_visited(t_stack *current, t_stack *visited);
static void	append_exits_to_last(t_stack **stack,
				t_room *curr_room, t_all_rooms *container);

// TODO: Fix error in this funciton, but still can't find what the
// error is.
static void	append_exits_to_last(t_stack **stack,
				t_room *curr_room, t_all_rooms *container)
{
	t_stack	*curr_stack;
	t_room	*room;
	char	*key;
	int		index;

	if (!stack || !curr_room || !container)
		return ;
	index = 0;
	while (index < curr_room->exits.len)
	{
		key = curr_room->exits.ids[index];
		room = get_room_from_id(container, key);
		if (room)
		{
			curr_stack = new_stack(room);
			stack_append(stack, curr_stack);
		}
		index ++;
	}
}

// Iterating ovre the visited stack, and see if the current
// one is inside, if yes, we return `true` overwise we return `false`
static bool	room_visited(t_stack *current, t_stack *visited)
{
	char	*curr_room_key;
	char	*neighboor_key;

	if (!current || !visited)
		return (false);
	curr_room_key = current->room->id;
	while (visited)
	{
		neighboor_key = visited->room->id;
		if (strcmp(curr_room_key, neighboor_key) == 0)
			return (true);
		visited = visited->next;
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
// room_finder(container, "philosophers.retreat");
bool	interconnection_checker(t_stack **stack,
			t_all_rooms *container, char **room_ids)
{
	t_stack	*visited;
	t_stack	*curr;
	int		counter;

	if (!stack || !*stack || !room_ids || !*room_ids)
		return (stack_free(*stack), false);
	visited = NULL;
	counter = 0;
	while (*stack)
	{
		curr = pop_first(stack);
		if (room_visited(curr, visited))
		{
			counter += 1;
			continue ;
		}
		stack_append(&visited, curr);
		curr->next = NULL;
		append_exits_to_last(stack, curr->room, container);
	}
	stack_free(visited);
	stack_free(*stack);
	return (counter >= INTERCONNECTION_BASE_COUNT);
}
