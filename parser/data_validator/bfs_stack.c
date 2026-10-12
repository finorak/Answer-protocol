/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 11:51:35 by finorako          #+#    #+#             */
/*   Updated: 2026/10/12 14:16:17 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../../includes/parser.h"

// Given a stack, we get the last element of that stack.
t_stack	*bfs_stack_last(t_stack *stack)
{
	if (!stack)
		return (stack);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

t_stack	*bfs_new_stack(void *data)
{
	t_stack	*stack;

	stack = (t_stack *)calloc(1, sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->data = data;
	stack->next = NULL;
	return (stack);
}

// Given a stack, we perform a pop left opration on it.
t_stack	*bfs_pop_first(t_stack **stack)
{
	t_stack	*head;

	if (!stack || !*stack)
		return (NULL);
	head = *stack;
	*stack = (*stack)->next;
	return (head);
}

// Given a stack, we append the new element to the stack.
t_stack	*bfs_stack_append(t_stack **current_stack, t_stack *new_el)
{
	t_stack	*last;

	if (!current_stack)
		return (NULL);
	if (!*current_stack)
	{
		*current_stack = new_el;
		return (*current_stack);
	}
	if (!(*current_stack)->data)
	{
		free(*current_stack);
		*current_stack = new_el;
		return (*current_stack);
	}
	last = bfs_stack_last(*current_stack);
	last->next = new_el;
	return (*current_stack);
}

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
