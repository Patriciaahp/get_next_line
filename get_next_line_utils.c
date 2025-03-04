/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:00:53 by pahernan          #+#    #+#             */
/*   Updated: 2025/03/04 16:07:36 by pahernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_strjoin(char *s1, char *s2)
{
	size_t len1 = ft_strlen(s1);
	size_t len2 = ft_strlen(s2);
	char *new_str;
	size_t i;
	size_t j;

	i = 0;
	j = 0;

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

	free(s1);
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

char *extract_line(char **resto)
{
	char *line;
	char *new_resto;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!*resto || **resto == '\0')
		return (NULL);
	while ((*resto)[i] && (*resto)[i] != '\n')
		i++;
	if (!(line = malloc(i + 2)))
		return (NULL);
	while (j <= i)
	{
		line[j] = (*resto)[j];
		j++;
	}
	line[i + 1] = '\0';
	if ((*resto)[i] == '\n')
		i++;
	new_resto = (*resto)[i] ? ft_strdup(*resto + i) : NULL;
	free(*resto);
	*resto = new_resto;
	return (line);
}
