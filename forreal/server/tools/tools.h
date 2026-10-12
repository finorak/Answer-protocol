/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irraheri <irraheri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 06:29:35 by irraheri          #+#    #+#             */
/*   Updated: 2026/10/12 06:30:16 by irraheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	add_player(int client_fd, t_world *world);
void	remove_player(int client_fd, t_world *world);

int     in(char *element, t_list_of list);
void	remove_from(char *element, t_list_of *list);
void	append_in(char *element, t_list_of *list);
