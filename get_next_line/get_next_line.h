/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 07:33:10 by finorako          #+#    #+#             */
/*   Updated: 2026/02/05 10:32:53 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_list
{
	struct s_list	*next;
	char			*content;
}					t_list;

typedef struct s_line
{
	char	*value;
	int		i;
	int		j;
}					t_line;

typedef struct s_current
{
	t_list	*temp;
	int		start;
	int		len;
}					t_current;

typedef struct s_start
{
	t_list	*lst;
	char	*value;
	char	last[BUFFER_SIZE + 1];
	int		byte_read;
}					t_start;

char				*get_next_line(int fd);

int					line_size(t_list *lst);

void				lstaddback(t_list **lst, char *content);

int					found_endl(t_list *lst);

char				*ft_memmove(char *dest, const char *src, int size);

int					get_next(char *content);
#endif
