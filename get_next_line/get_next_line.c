/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 07:41:42 by finorako          #+#    #+#             */
/*   Updated: 2026/02/06 09:52:44 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		index++;
	}
	return (index);
}

static char	*get_line(t_list *lst)
{
	t_line	line;

	if (!lst)
		return (NULL);
	line.value = (char *)malloc(sizeof(char) * (line_size(lst) + 1));
	if (!line.value)
		return (NULL);
	line.i = 0;
	while (lst)
	{
		line.j = 0;
		while (lst->content[line.j] && lst->content[line.j] != '\n')
			line.value[line.i++] = lst->content[line.j++];
		if (lst->content[line.j] == '\n')
		{
			line.value[line.i++] = '\n';
			break ;
		}
		lst = lst->next;
	}
	line.value[line.i] = '\0';
	return (line.value);
}

static char	*sub_dup(char *buffer, int size)
{
	t_line	line;

	line.value = (char *)malloc(sizeof(char) * (size + 1));
	if (!line.value)
		return (NULL);
	line.i = 0;
	while (line.i < size)
	{
		line.value[line.i] = buffer[line.i];
		line.i++;
	}
	line.value[line.i] = '\0';
	return (line.value);
}

void	cleanlst(t_list **lst, char *remain)
{
	t_current	curr;

	if (!lst || !*lst)
		return ;
	while ((*lst)->next)
	{
		curr.temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = curr.temp;
	}
	remain[0] = '\0';
	if ((*lst)->content)
	{
		curr.start = get_next((*lst)->content);
		if (curr.start >= 0)
			ft_memmove(remain, (*lst)->content + curr.start,
				ft_strlen((*lst)->content + curr.start) + 1);
	}
	else
		remain[0] = '\0';
	free((*lst)->content);
	free(*lst);
	*lst = NULL;
}

char	*get_next_line(int fd)
{
	static t_start	start = {NULL, NULL, {0}, 0};
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (start.last[0] != '\0')
		lstaddback(&start.lst, sub_dup(start.last, ft_strlen(start.last)));
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!found_endl(start.lst))
	{
		start.byte_read = read(fd, buffer, BUFFER_SIZE);
		if (start.byte_read <= 0)
			break ;
		lstaddback(&start.lst, sub_dup(buffer, start.byte_read));
	}
	free(buffer);
	if (line_size(start.lst) == 0)
		cleanlst(&start.lst, start.last);
	start.value = get_line(start.lst);
	cleanlst(&start.lst, start.last);
	return (start.value);
}
