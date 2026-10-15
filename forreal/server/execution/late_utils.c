/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   late_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:43:57 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/15 16:43:57 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	strcat_number(char *message, int number)
{
	char	temp[12];

	sprintf(temp, "%d", number);
	strcat(message, temp);
}
