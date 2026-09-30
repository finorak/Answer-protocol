/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_extractor.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 10:22:05 by finorako          #+#    #+#             */
/*   Updated: 2026/09/30 18:44:13 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_EXTRACTOR_H
# define DATA_EXTRACTOR_H

# include <stdlib.h>
# include <stdio.h>
# include "world.h"
# include "cJSON.h"

# define ITEMS_KEY "items"
# define ROOM_KEY "world"

t_all_rooms	*extract_rooms(cJSON *root);
t_all_items	*extract_items(cJSON *root);

#endif // !DATA_EXTRACTOR_H
