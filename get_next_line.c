/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:41:06 by pahernan          #+#    #+#             */
/*   Updated: 2025/03/05 13:48:34 by pahernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
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
	return (NULL);
}

char	*ft_invalid(char **resto)
{
	if (*resto)
	{
		free(*resto);
		*resto = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*resto;
	char		*buffer;
	ssize_t		bytes_leidos;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (ft_invalid(&resto));
	buffer = ft_getbuffer(buffer);
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

char	*ft_getbuffer(char *buffer)
{
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	return (buffer);
}
