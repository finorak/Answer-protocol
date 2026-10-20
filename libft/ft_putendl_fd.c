/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:17:54 by finorako          #+#    #+#             */
/*   Updated: 2026/01/23 22:17:58 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char *str, int fd)
{
	if (!str)
	{
		write(fd, "\n", 1);
		return ;
	}
	while (*str)
		write(fd, str++, 1);
	write(fd, "\n", 1);
}
