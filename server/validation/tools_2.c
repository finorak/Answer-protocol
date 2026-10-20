/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:27:27 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/17 20:05:49 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../main_utils.h"

void	one_word_parsing_mess(t_command test, t_command *result)
{
	if (!result)
		return ;
	result->is_valid = 1;
	strcpy(result->message, test.message);
	if (!strcmp(test.type, "CONNECT") || !strcmp(test.type, "MOVE")
		|| !strcmp(test.type, "TAKE") || !strcmp(test.type, "DROP")
		|| !strcmp(test.type, "TALK") || !strcmp(test.type, "ATTACK")
		|| !strcmp(test.type, "QUEST") || !strcmp(test.type, "COMPLETE_QUEST"))
		strcpy(result->type, test.type);
	else
	{
		result->is_valid = 0;
		strcpy(result->type, "ERROR");
		strcpy(result->message, "ERR 901 SEND_FAILED\n");
	}
}

static int	intermediate_step(t_command test, t_command *result, int chat)
{
	if (!result)
		return (0);
	strcat(result->type, test.message);
	restore_from_first_term(test.message);
	not_first_term(test.message);
	if (chat == 1)
	{
		strcpy(result->message, test.message);
		return (1);
	}
	else
	{
		if (first_term(test.message) == 0)
		{
			strcpy(result->message, test.message);
			return (1);
		}
	}
	return (0);
}

static int	chat_and_group_management(t_command test, t_command *result)
{
	if (!result)
		return (0);
	if (!strcmp(test.type, "CHAT"))
	{
		if (!strcmp(test.message, "GLOBAL") || !strcmp(test.message, "ROOM")
			|| !strcmp(test.message, "GROUP"))
			return (intermediate_step(test, result, 1));
	}
	else
	{
		if (!strcmp(test.message, "CREATE") || !strcmp(test.message, "INVITE")
			|| !strcmp(test.message, "JOIN") || !strcmp(test.message, "LEAVE"))
			return (intermediate_step(test, result, 0));
	}
	return (0);
}

void	first_word_parsing_mess(t_command test, t_command *result)
{
	if (!result)
		return ;
	result->is_valid = 1;
	strcpy(result->type, test.type);
	if (!strcmp(test.type, "TAKE") || !strcmp(test.type, "DROP"))
	{
		restore_from_first_term(test.message);
		strcpy(result->message, test.message);
		return ;
	}
	else
	{
		if (chat_and_group_management(test, result) == 1)
			return ;
	}
	result->is_valid = 0;
	strcpy(result->type, "ERROR");
	strcpy(result->message, "ERR 901 SEND_FAILED\n");
}
