/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:48:52 by fdi-tria          #+#    #+#             */
/*   Updated: 2024/11/12 19:51:27 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_read_and_append(int fd, t_buffer *buf, char *tmp_buf)
{
	ssize_t	r;

	while (1)
	{
		r = read(fd, tmp_buf, BUFFER_SIZE);
		if (r < 0)
			return (-1);
		if (r == 0)
			return (0);
		if (ft_append_buffer(buf, tmp_buf, r) == -1)
			return (-1);
		if (ft_memchr(tmp_buf, '\n', r))
			return (1);
	}
}

static int	ft_read_file(int fd, t_buffer *buf)
{
	char	*tmp_buf;
	int		result;

	tmp_buf = malloc(BUFFER_SIZE);
	if (!tmp_buf)
		return (-1);
	result = ft_read_and_append(fd, buf, tmp_buf);
	free(tmp_buf);
	if (result == -1)
		return (-1);
	return (0);
}

static char	*ft_get_line(t_buffer *buf)
{
	size_t	i;
	char	*line;

	if (!buf->data || buf->len == 0)
		return (NULL);
	i = 0;
	while (i < buf->len && buf->data[i] != '\n')
		i++;
	if (i < buf->len && buf->data[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, buf->data, i);
	line[i] = '\0';
	return (line);
}

static void	ft_update_buffer(t_buffer *buf)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < buf->len && buf->data[i] != '\n')
		i++;
	if (i < buf->len && buf->data[i] == '\n')
		i++;
	j = 0;
	while (i + j < buf->len)
	{
		buf->data[j] = buf->data[i + j];
		j++;
	}
	buf->len = j;
	buf->data[buf->len] = '\0';
}

char	*get_next_line(int fd)
{
	static t_buffer	buf = {NULL, 0, 0};
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_handle_error(&buf);
		return (NULL);
	}
	if (ft_read_file(fd, &buf) == -1)
	{
		ft_handle_error(&buf);
		return (NULL);
	}
	line = ft_get_line(&buf);
	if (!line)
	{
		ft_handle_error(&buf);
		return (NULL);
	}
	ft_update_buffer(&buf);
	return (line);
}
