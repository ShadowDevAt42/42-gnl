/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdi-tria <fdi-tria@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:49:00 by fdi-tria          #+#    #+#             */
/*   Updated: 2024/11/12 04:23:29 by fdi-tria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_handle_error(char *buf, char *s)
{
	if (buf)
		free(buf);
	if (s)
		free(s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

static char	*ft_join_check(char *s1, char *s2, char **str)
{
	if (!s1 || !s2)
		return (NULL);
	if (!s1[0] && !s2[0])
	{
		free(s1);
		return (NULL);
	}
	*str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!*str)
	{
		free(s1);
		return (NULL);
	}
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	s1 = ft_join_check(s1, s2, &str);
	if (!s1)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}
