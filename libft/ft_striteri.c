/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:19:05 by finorako          #+#    #+#             */
/*   Updated: 2026/01/23 22:19:10 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *str, void (*f)(unsigned int, char *))
{
	unsigned int	index;

	if (!str || !f)
		return ;
	index = 0;
	while (str[index])
	{
		f(index, &str[index]);
		index++;
	}
}
