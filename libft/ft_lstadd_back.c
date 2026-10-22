/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:44:19 by finorako          #+#    #+#             */
/*   Updated: 2026/01/26 10:34:09 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_lst)
{
	t_list	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new_lst;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new_lst;
}
