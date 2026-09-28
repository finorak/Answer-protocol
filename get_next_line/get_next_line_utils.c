/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 07:35:58 by finorako          #+#    #+#             */
/*   Updated: 2026/02/05 10:24:24 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

void	lstaddback(t_list **lst, char *content)
{
	t_list	*new_lst;
	t_list	*last;

	if (!content || *content == '\0')
		return ;
	new_lst = (t_list *)malloc(sizeof(t_list));
	if (!new_lst)
		return ;
	new_lst->content = content;
	new_lst->next = NULL;
	if (*lst == NULL)
	{
		*lst = new_lst;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new_lst;
}

int	found_endl(t_list *lst)
{
	int	index;

	while (lst)
	{
		index = 0;
		while (lst->content[index] && lst->content[index] != '\n')
			index++;
		if (lst->content[index] == '\n')
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	line_size(t_list *lst)
{
	t_line	line;

	line.i = 0;
	while (lst)
	{
		line.j = 0;
		while (lst->content[line.j] && lst->content[line.j] != '\n')
		{
			line.i++;
			line.j++;
		}
		if (lst->content[line.j] == '\n')
			return (++line.i);
		lst = lst->next;
	}
	return (line.i);
}

int	get_next(char *content)
{
	int	index;

	index = 0;
	while (content[index] && content[index] != '\n')
		index++;
	if (content[index] == '\n')
		return (++index);
	return (-1);
}

char	*ft_memmove(char *dest, const char *src, int size)
{
	int		index;

	if (dest > src)
	{
		while (size--)
			dest[size] = src[size];
	}
	else
	{
		index = 0;
		while (index < size)
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (dest);
}
