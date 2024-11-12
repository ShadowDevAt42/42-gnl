/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:49:00 by fdi-tria          #+#    #+#             */
/*   Updated: 2024/11/12 05:27:39 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_handle_error(t_buffer *buf)
{
	if (buf)
	{
		if (buf->data)
			free(buf->data);
		buf->data = NULL;
		buf->len = 0;
		buf->capacity = 0;
	}
}

int	ft_append_buffer(t_buffer *buf, char *data, size_t data_len)
{
	char	*new_data;
	size_t	new_capacity;

	if (buf->len + data_len + 1 > buf->capacity)
	{
		new_capacity = buf->capacity * 2 + data_len + 1;
		new_data = malloc(new_capacity);
		if (!new_data)
			return (-1);
		if (buf->data)
		{
			ft_memcpy(new_data, buf->data, buf->len);
			free(buf->data);
		}
		buf->data = new_data;
		buf->capacity = new_capacity;
	}
	ft_memcpy(buf->data + buf->len, data, data_len);
	buf->len += data_len;
	buf->data[buf->len] = '\0';
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (!dst && !src)
		return (NULL);
	d = (char *)dst;
	s = (const char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;

	ptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}
