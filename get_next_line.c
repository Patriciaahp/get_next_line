/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:41:06 by pahernan          #+#    #+#             */
/*   Updated: 2025/04/02 14:41:34 by pahernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *buff)
{
	char	*tmp;
	char	*line;
	char	*new_line;
	ssize_t	bytes_read;

	line = ft_strjoin(buff, "");
	while (!ft_strchr(line, '\n'))
	{
		tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!tmp)
			return (free(line), NULL);
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(line), free(tmp), NULL);
		if (bytes_read == 0)
			return (free(tmp), line);
		tmp[bytes_read] = '\0';
		new_line = ft_strjoin(line, tmp);
		free(line);
		free(tmp);
		line = ft_strdup(new_line);
		free(new_line);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_file(fd, buff);
	if (!line)
		return (buff[0] = '\0', NULL);
	if (!line[0])
		return (free(line), NULL);
	if (!ft_strchr(line, '\n'))
		return (ft_strcpy(buff, ""), line);
	ft_strcpy(buff, ft_strchr(line, '\n') + 1);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n' && line[i + 1])
		line[i + 1] = '\0';
	return (line);
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