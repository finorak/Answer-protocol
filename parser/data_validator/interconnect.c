/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interconnect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 12:57:23 by finorako          #+#    #+#             */
/*   Updated: 2026/10/12 14:16:01 by finorako         ###   ########.fr       */
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
	int		index;

	if (!stack || !curr_room || !container)
		return ;
	index = 0;
	printf("here %d\n", curr_room->exits.len);
	return ;
	while (index < curr_room->exits.len)
	{
		if (!strcmp(curr_room->exits.ids[index], "none"))
		{
			index ++;
			continue ;
		}
		if (index >= curr_room->exits.len)
		{
			printf("overflow\n");
			break ;
		}
		curr_stack = bfs_new_stack(
				get_room_from_id(container, curr_room->exits.ids[index]));
		last = bfs_stack_last(*stack);
		last->next = curr_stack;
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
		if (!seen->data)
		{
			seen = seen->next;
			continue ;
		}
		exits_key = (char *)((t_room *)seen->data)->id;
		printf("(%s, %s)\n", curr_key, exits_key);
		if (strcmp(curr_key, exits_key) == 0)
			return (true);
		seen = seen->next;
	}
	return (false);
}

bool	room_interconnect(t_stack **stack,
			t_all_rooms *container, char **room_ids)
{
	t_stack	*seen;
	t_stack	*curr;
	bool	valid;

	if (!room_ids)
		return (false);
	if (!stack)
		return (stack_free(*stack), false);
	seen = bfs_new_stack(NULL);
	if (!seen)
		return (stack_free(*stack), false);
	valid = true;
	while (*stack)
	{
		curr = bfs_pop_first(stack);
		if (room_visited(curr, seen))
			continue ;
		bfs_stack_append(&seen, curr);
		append_exits_to_last(stack, (t_room *)curr->data, container);
	}
	stack_free(seen);
	stack_free(*stack);
	return (valid);
}
