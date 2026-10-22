/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:25:32 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/21 19:08:06 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "../../includes/world.h"

int			first_term(char *str);
void		one_word_parsing(char *buf, t_command *result);
void		first_word_parsing(char *buf, t_command *result);
void		restore_from_first_term(char *str);
void		not_first_term(char *str);
t_command	validation_1(char *buf);
void		one_word_parsing_mess(t_command test, t_command *result);
void		first_word_parsing_mess(t_command test, t_command *result);
t_command	validation_2(t_command test);

#endif
