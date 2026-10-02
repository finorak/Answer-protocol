/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 14:51:44 by finorako          #+#    #+#             */
/*   Updated: 2026/10/02 14:52:47 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_missions(t_all_missions *items, int size)
{
	int	index;

	if (!items)
		return ;
	index = 0;
	while (index < size)
	{
		free(items->missions[index]);
		index ++;
	}
	free(items);
}

void	free_dialogues(t_all_dialogues *items, int size)
{
	int	index;

	if (!items)
		return ;
	index = 0;
	while (index < size)
	{
		free(items->dialogues[index]);
		index += 1;
	}
	free(items);
}

void	free_groups(t_all_groups *groups, int size)
{
	int	index;

	if (!groups)
		return ;
	index = 0;
	while (index < size)
	{
		printf("%s\n", groups->groups[index]->name);
		free(groups->groups[index]);
		index += 1;
	}
	free(groups);
}
