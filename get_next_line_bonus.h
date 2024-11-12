/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 05:41:05 by fdi-tria          #+#    #+#             */
/*   Updated: 2024/11/12 19:51:42 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_fd_list
{
	int					fd;
	char				*data;
	size_t				len;
	size_t				capacity;
	struct s_fd_list	*next;
}	t_fd_list;

char		*get_next_line(int fd);
int			ft_append_buffer(t_fd_list *node, char *data, size_t data_len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
t_fd_list	*ft_get_fd_node(t_fd_list **head, int fd);
void		ft_remove_fd_node(t_fd_list **head, int fd);

#endif