/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:40:35 by pahernan          #+#    #+#             */
/*   Updated: 2025/03/11 12:12:27 by pahernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

int ft_strlen(const char *str);
char *ft_strchr(const char *s, int c);
char *ft_strjoin(char *s1, char *s2);
char *ft_strdup(const char *s);
char *extract_line(char **rest);
char *get_next_line(int fd);
void ft_strlcpy(char *dst, const char *src, size_t *index);
char *get_new_rest(char *rest, int i);
char *ft_invalid(char **rest);

#endif