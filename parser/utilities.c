/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megalonia </var/spool/mail/megalonia>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 14:07:22 by megalonia         #+#    #+#             */
/*   Updated: 2026/10/18 14:12:30 by megalonia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/data_extractor.h"
#include <stdbool.h>

bool	is_string(const cJSON *content)
{
	return (content && cJSON_IsString(content));
}

bool	is_array(const cJSON *content)
{
	return (content && cJSON_IsArray(content));
}

bool	is_object(const cJSON *content)
{
	return (content && cJSON_IsObject(content));
}

bool	is_number(const cJSON *content)
{
	return (content && cJSON_IsNumber(content));
}
