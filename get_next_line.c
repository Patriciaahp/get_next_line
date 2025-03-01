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

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

static size_t ft_strlen(const char *str)
{
    size_t i = 0;
    while (str && str[i])
        i++;
    return (i);
}

static char *ft_strchr(const char *s, int c)
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

static char *ft_strjoin(char *s1, char *s2)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *new_str;
    size_t i = 0, j = 0;

    new_str = malloc(len1 + len2 + 1);
    if (!new_str)
        return (NULL);
    while (i < len1)
    {
        new_str[i] = s1[i];
        i++;
    }
    while (j < len2)
        new_str[i++] = s2[j++];
    new_str[i] = '\0';

    free(s1); // Liberar la memoria antigua de s1 (resto)
    return (new_str);
}

char *ft_strdup(const char *s)
{
    char *s2;
    int i;

    i = 0;
    while (s[i])
        i++;
    s2 = malloc(sizeof(char) * (i + 1));
    if (!s2)
        return (NULL);
    i = 0;
    while (s[i] != '\0')
    {
        s2[i] = s[i];
        i++;
    }
    s2[i] = '\0';
    if (s2 != NULL)
        return (s2);
    return (NULL);
}

static char *extract_line(char **resto)
{
    char *line;
    char *new_resto;
    int i = 0;

    if (!*resto || **resto == '\0')
        return (NULL);

    while ((*resto)[i] && (*resto)[i] != '\n')
        i++;
    line = malloc(i + 2);
    if (!line)
        return (NULL);

    for (int j = 0; j <= i; j++)
        line[j] = (*resto)[j];
    line[i + 1] = '\0';

    if ((*resto)[i] == '\n')
        i++;

    new_resto = (*resto)[i] ? ft_strdup(*resto + i) : NULL;
    free(*resto);
    *resto = new_resto;

    return (line);
}

char *get_next_line(int fd)
{
    static char *resto;
    char *buffer;
    ssize_t bytes_leidos;

    if (fd < 0 || BUFFER_SIZE <= 0 || !(buffer = malloc(BUFFER_SIZE + 1)))
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

int main()
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
}