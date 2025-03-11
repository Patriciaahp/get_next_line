/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:41:06 by pahernan          #+#    #+#             */
/*   Updated: 2025/03/11 12:29:10 by pahernan         ###   ########.fr       */
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
	int			bytes_leidos;
	char		*temp;
	char		*line;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (ft_invalid(&resto));
	buffer = ft_getbuffer();
	if (!buffer)
		return (ft_invalid(&resto));
	while (!ft_strchr(resto, '\n'))
	{
		bytes_leidos = read(fd, buffer, BUFFER_SIZE);
		if (bytes_leidos <= 0)
		{
			free(buffer);
			if (resto && *resto)
			{
				line = extract_line(&resto);
				if (!line)
				{
					free(resto);
					resto = NULL;
				}
				return (line);
			}
			return (ft_invalid(&resto));
		}
		buffer[bytes_leidos] = '\0';
		temp = ft_strjoin(resto, buffer);
		free(resto);
		resto = temp;
		if (!resto)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (extract_line(&resto));
}

char	*ft_getbuffer()
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		return (NULL);
	}
	return (buffer);
}

/* % gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c 
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