/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 05:40:03 by fdi-tria          #+#    #+#             */
/*   Updated: 2024/11/12 06:06:01 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_read_and_append(int fd, t_fd_list *node, char *tmp_buf)
{
	ssize_t	r;

	while (1)
	{
		r = read(fd, tmp_buf, BUFFER_SIZE);
		if (r < 0)
			return (-1);
		if (r == 0)
			break ;
		if (ft_append_buffer(node, tmp_buf, r) == -1)
			return (-1);
		if (ft_memchr(tmp_buf, '\n', r))
			break ;
	}
	return (0);
}

static int	ft_read_file(int fd, t_fd_list *node)
{
	char	*tmp_buf;
	int		result;

	tmp_buf = malloc(BUFFER_SIZE);
	if (!tmp_buf)
		return (-1);
	result = ft_read_and_append(fd, node, tmp_buf);
	free(tmp_buf);
	return (result);
}

static char	*ft_get_line(t_fd_list *node)
{
	size_t	i;
	char	*line;

	if (!node->data || node->len == 0)
		return (NULL);
	i = 0;
	while (i < node->len && node->data[i] != '\n')
		i++;
	if (i < node->len && node->data[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, node->data, i);
	line[i] = '\0';
	return (line);
}

static void	ft_update_buffer(t_fd_list *node)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < node->len && node->data[i] != '\n')
		i++;
	if (i < node->len && node->data[i] == '\n')
		i++;
	j = 0;
	while (i + j < node->len)
	{
		node->data[j] = node->data[i + j];
		j++;
	}
	node->len = j;
	node->data[node->len] = '\0';
}

char	*get_next_line(int fd)
{
	static t_fd_list	*head;
	t_fd_list			*node;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = ft_get_fd_node(&head, fd);
	if (!node || ft_read_file(fd, node) == -1)
	{
		ft_remove_fd_node(&head, fd);
		return (NULL);
	}
	line = ft_get_line(node);
	if (!line)
	{
		ft_remove_fd_node(&head, fd);
		return (NULL);
	}
	ft_update_buffer(node);
	if (node->len == 0)
		ft_remove_fd_node(&head, fd);
	return (line);
}
