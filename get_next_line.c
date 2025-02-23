/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:41:06 by pahernan          #+#    #+#             */
/*   Updated: 2025/02/23 18:41:06 by pahernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char *get_next_line(int fd)
{
    if (fd < 0)
        return NULL;

    char *buffer = malloc(2);
    if (!buffer)
        return NULL;

    ssize_t bytes_leidos = read(fd, buffer, 1);
    if (bytes_leidos <= 0)
    {
        free(buffer);
        return NULL;
    }

    buffer[1] = '\0';
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