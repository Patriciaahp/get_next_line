/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:41:06 by pahernan          #+#    #+#             */
/*   Updated: 2025/04/03 13:25:55 by pahernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*rest[4096];
	char		*buffer;
	int			bytes;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_invalid(&rest[fd]));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_invalid(&rest[fd]));
	bytes = 1;
	while (!ft_strchr(rest[fd], '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (ft_invalid(&rest[fd]));
		}
		buffer[bytes] = '\0';
		rest[fd] = ft_strjoin(rest[fd], buffer);
	}
	free(buffer);
	return (extract_line(&rest[fd]));
}

/* cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
get_next_line.h*/
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