/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:41:06 by pahernan          #+#    #+#             */
/*   Updated: 2025/04/01 23:24:01 by pahernan         ###   ########.fr       */
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

char	*ft_invalid(char **rest)
{
	if (*rest)
	{
		free(*rest);
		*rest = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buffer;
	int			bytes;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (ft_invalid(&rest));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_invalid(&rest));
	while (!ft_strchr(rest, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
		{
			free(buffer);
			if (rest && *rest)
				return (extract_line(&rest));
			return (NULL);
		}
		buffer[bytes] = '\0';
		rest = ft_strjoin(rest, buffer);
	}
	free(buffer);
	return (extract_line(&rest));
}

/* cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
get_next_line.h -o gnl*/
/*int main()
{
	int fd = open("archivo.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return 1;
	}

	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return 0;
}*/