/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako  </var/spool/mail/megalonia>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 17:00:17 by finorako          #+#    #+#             */
/*   Updated: 2026/10/16 18:01:13 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "world.h"

void	exit_printer(t_all_rooms *container, char *room_id);
void	print_exits(t_room *room);

#endif
