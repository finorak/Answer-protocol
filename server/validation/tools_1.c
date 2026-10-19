/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:27:30 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 20:05:57 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../main_utils.h"

int	first_term(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (i == (int)strlen(str))
		return (0);
	str[i] = '\0';
	return (1);
}

void	one_word_parsing(char *buf, t_command *result)
{
	result->is_valid = 1;
	strcpy(result->message, "one column message");
	if (!strcmp(buf, "LOOK") || !strcmp(buf, "QUIT") || !strcmp(buf, "WHO")
		|| !strcmp(buf, "INVENTORY") || !strcmp(buf, "STATUS") || !strcmp(buf,
			"QUESTS"))
	{
		strcpy(result->type, buf);
		return ;
	}
	result->is_valid = 0;
	strcpy(result->type, "ERROR");
	strcpy(result->message, "ERR 901 SEND_FAILED\n");
}

void	first_word_parsing(char *buf, t_command *result)
{
	result->is_valid = 1;
	if (!strcmp(buf, "CONNECT") || !strcmp(buf, "MOVE") || !strcmp(buf, "TAKE")
		|| !strcmp(buf, "DROP") || !strcmp(buf, "TALK") || !strcmp(buf,
			"ATTACK") || !strcmp(buf, "QUEST") || !strcmp(buf, "CHAT")
		|| !strcmp(buf, "GROUP") || !strcmp(buf, "COMPLETE_QUEST"))
	{
		strcpy(result->type, buf);
		return ;
	}
	result->is_valid = 0;
	strcpy(result->type, "ERROR");
	strcpy(result->message, "ERR 901 SEND_FAILED\n");
}

void	restore_from_first_term(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	str[i] = ' ';
}

void	not_first_term(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (i == (int)strlen(str))
		return ;
	i++;
	while (str[i])
	{
		str[j] = str[i];
		j++;
		i++;
	}
	str[j] = '\0';
}
