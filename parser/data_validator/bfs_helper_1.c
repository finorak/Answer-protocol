/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_helper_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 11:51:35 by finorako          #+#    #+#             */
/*   Updated: 2026/10/16 18:01:00 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../../includes/parser.h"

// Given a stack, we get the last element of that stack.
t_stack	*get_last_stack(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

// Creating a new stack.
// Might change the data passed to be a `void *`
// so that our implementation become more modulable.
t_stack	*new_stack(t_room *room)
{
	t_stack	*stack;

	if (!room)
		return (NULL);
	stack = (t_stack *)calloc(1, sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->room = room;
	stack->next = NULL;
	return (stack);
}

// Given a stack, we perform a pop left opration on it.
t_stack	*pop_first(t_stack **stack)
{
	t_stack	*head;

	if (!stack || !*stack)
		return (NULL);
	head = *stack;
	*stack = (*stack)->next;
	head->next = NULL;
	return (head);
}

// Given a stack, we append the new element to the stack.
t_stack	*stack_append(t_stack **stack, t_stack *new_stack)
{
	t_stack	*last;

	if (!stack)
		return (NULL);
	if (!*stack || !(*stack)->room)
	{
		free(*stack);
		*stack = new_stack;
		return (*stack);
	}
	last = get_last_stack(*stack);
	if (last)
		last->next = new_stack;
	return (*stack);
}

// Release the stack and it's child node from
// memory to avoid memory leak
void	stack_free(t_stack *stack)
{
	t_stack	*tmp;

	if (!stack)
		return ;
	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
	free(stack);
}
