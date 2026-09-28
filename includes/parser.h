/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 10:02:11 by finorako          #+#    #+#             */
/*   Updated: 2026/09/28 14:56:53 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

typedef struct s_string_view
{
	struct s_string_view		*next;
	char						buffer[1024];
	int							len;
}								t_string_view;

typedef struct s_data
{
	t_string_view				*lines;
}								t_data;

// stack manipulator
t_string_view					*get_last_string(t_string_view *string);
t_string_view					*new_string_view(char *string);

// data initialisation
bool							init_data(t_data *data, char *config);

// memroy managment
void							free_string_view(t_string_view *string);
void							free_data(t_data *data);

// DEBUG
// void							print_log(t_data *data);
#endif // !PARSER_H
