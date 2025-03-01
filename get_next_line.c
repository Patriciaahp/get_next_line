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

int ft_strlen(const char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

char *ft_strchr(const char *s, int c)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == (char)c)
            return (char *)(s + i);
        i++;
    }
    if (c == '\0' && s[i] == '\0')
        return (char *)(s + i);
    return NULL;
}

char *ft_strjoin(const char *s1, const char *s2)
{
    int len1 = ft_strlen(s1);
    int len2 = ft_strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    int i = 0;

    if (!result)
        return NULL;

    while (i < len1)
    {
        result[i] = s1[i];
        i++;
    }
    while (i < len1 + len2)
    {
        result[i] = s2[i - len1];
        i++;
    }
    result[i] = '\0';
    return result;
}

char *extract_line(char **resto)
{
    int i = 0;
    while ((*resto)[i] && (*resto)[i] != '\n')
        i++;

    char *line = malloc(i + 2);
    if (!line)
        return NULL;

    int j = 0;
    while (j <= i)
    {
        line[j] = (*resto)[j];
        j++;
    }
    line[j] = '\0';

    char *new_resto = NULL;
    if ((*resto)[i] == '\n')
        i++;

    if ((*resto)[i] != '\0')
        new_resto = ft_strjoin(*resto + i, "");
    free(*resto);
    *resto = new_resto;

    return line;
}

char *get_next_line(int fd)
{
    static char *resto = NULL;
    char *buffer = malloc(BUFFER_SIZE + 1);
    if (fd < 0 || BUFFER_SIZE <= 0 || !buffer)
        return NULL;

    int bytes_leidos = 1;
    while (!ft_strchr(resto, '\n') && bytes_leidos > 0)
    {
        bytes_leidos = read(fd, buffer, BUFFER_SIZE);
        if (bytes_leidos <= 0)
        {
            free(buffer);
            if (resto && *resto)
                return extract_line(&resto);
            return NULL;
        }
        buffer[bytes_leidos] = '\0';
        resto = ft_strjoin(resto, buffer);
    }

    free(buffer);
    return extract_line(&resto);
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