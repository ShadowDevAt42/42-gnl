/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 05:40:40 by fdi-tria          #+#    #+#             */
/*   Updated: 2024/11/12 19:51:41 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_append_buffer(t_fd_list *node, char *data, size_t data_len)
{
	char	*new_data;
	size_t	new_capacity;

	if (node->len + data_len + 1 > node->capacity)
	{
		new_capacity = node->capacity * 2 + data_len + 1;
		new_data = malloc(new_capacity);
		if (!new_data)
			return (-1);
		if (node->data)
		{
			ft_memcpy(new_data, node->data, node->len);
			free(node->data);
		}
		node->data = new_data;
		node->capacity = new_capacity;
	}
	ft_memcpy(node->data + node->len, data, data_len);
	node->len += data_len;
	node->data[node->len] = '\0';
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

t_fd_list	*ft_get_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*node;

	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->data = NULL;
	node->len = 0;
	node->capacity = 0;
	node->next = *head;
	*head = node;
	return (node);
}

void	ft_remove_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*prev;
	t_fd_list	*curr;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		if (curr->fd == fd)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			if (curr->data)
				free(curr->data);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
