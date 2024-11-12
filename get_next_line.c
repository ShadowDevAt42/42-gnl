/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:48:52 by fdi-tria          #+#    #+#             */
/*   Updated: 2024/11/12 04:42:52 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_init_buffer(char **buf, char *s)
{
	*buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!*buf)
		return (ft_handle_error(NULL, s));
	if (!s)
	{
		s = malloc(1);
		if (!s)
			return (ft_handle_error(*buf, NULL));
		s[0] = '\0';
	}
	return (s);
}

static char	*ft_read_file(int fd, char *s)
{
	char	*buf;
	int		r;

	s = ft_init_buffer(&buf, s);
	if (!s)
		return (NULL);
	r = 1;
	while (r > 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
			return (ft_handle_error(buf, s));
		buf[r] = '\0';
		s = ft_strjoin(s, buf);
		if (!s)
			return (ft_handle_error(buf, NULL));
		if (r < BUFFER_SIZE || ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (s);
}

static char	*ft_get_line(char *s)
{
	char	*line;
	int		i;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_next(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	str = malloc(ft_strlen(s) - i);
	if (!str)
	{
		free(s);
		return (NULL);
	}
	i++;
	j = 0;
	while (s[i])
		str[j++] = s[i++];
	str[j] = '\0';
	free(s);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (save)
			free(save);
		save = NULL;
		return (NULL);
	}
	save = ft_read_file(fd, save);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	if (!line)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = ft_next(save);
	return (line);
}
