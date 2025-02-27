/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:41:06 by pahernan          #+#    #+#             */
/*   Updated: 2025/02/27 12:42:25 by pahernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (src[j] != '\0')
		j++;
	if (size == 0)
		return (j);
	while ((src[i] != '\0') && (size != 1))
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	if (size > 0)
		dst[i] = '\0';
	return (j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	s3 = malloc(sizeof(char) * (i + j + 1));
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, i + 1);
	ft_strlcpy(s3 + i, s2, j + 1);
	return (s3);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str)
		i++;
	return (i);
}

char *ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if ((char)c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (*s)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char *get_next_line(int fd)
{
	//cambiar buffer por BUFFER_SIZE
	int	i;

	i = 0;
	if (fd < 0)
	return NULL;
    char *buffer = malloc(20);

    if (!buffer)
        return NULL;

    ssize_t bytes_leidos = read(fd, buffer, 20);
    if (bytes_leidos <= 0)
    {
        free(buffer);
        return NULL;
    }

    buffer[17] = '\0';
    return buffer;
}

int main()
{
    int fd = open("archivo.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return 1;
    }

    char *letra = get_next_line(fd);
    if (letra)
    {
        printf("Letra leída: %s\n", letra);
        free(letra);
    }
    else
    {
        printf("No se pudo leer una letra.\n");
    }

    close(fd);
    return 0;
}