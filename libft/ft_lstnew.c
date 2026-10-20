/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:16:19 by finorako          #+#    #+#             */
/*   Updated: 2026/01/23 22:16:22 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list			*list;

	list = (t_list *)(malloc(sizeof(t_list)));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
