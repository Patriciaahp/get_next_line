/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pahernan <pahernan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:00:53 by pahernan          #+#    #+#             */
/*   Updated: 2025/03/11 09:44:31 by pahernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	int		i;

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

void	ft_strlcpy(char *dst, const char *src, size_t *index)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[*index] = src[i];
		i++;
		(*index)++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;
	size_t	i;

	i = 0;
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (free(s1), NULL);
	ft_strlcpy(new_str, s1, &i);
	ft_strlcpy(new_str, s2, &i);
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}

char	*get_new_resto(char *resto, int i)
{
	char	*new_resto;

	new_resto = NULL;
	if (resto[i] != '\0')
		new_resto = ft_strdup(resto + i);
	free(resto);
	return (new_resto);
}

char	*extract_line(char **resto)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!*resto || **resto == '\0')
		return (NULL);
	while ((*resto)[i] && (*resto)[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	while (j <= i)
	{
		line[j] = (*resto)[j];
		j++;
	}
	line[i + 1] = '\0';
	if ((*resto)[i] == '\n')
		i++;
	*resto = get_new_resto(*resto, i);
	return (line);
}
