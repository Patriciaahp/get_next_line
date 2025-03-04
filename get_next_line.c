/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:41:06 by pahernan          #+#    #+#             */
/*   Updated: 2025/03/04 18:17:06 by pahernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char *ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char *get_next_line(int fd)
{
	static char *resto;
	char *buffer;
	ssize_t bytes_leidos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(resto, '\n'))
	{
		bytes_leidos = read(fd, buffer, BUFFER_SIZE);
		if (bytes_leidos <= 0)
		{
			free(buffer);
			if (resto && *resto)
				return (extract_line(&resto));
			return (NULL);
		}
		buffer[bytes_leidos] = '\0';
		resto = ft_strjoin(resto, buffer);
	}
	free(buffer);
	return (extract_line(&resto));
}