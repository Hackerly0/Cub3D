/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:57:29 by maemran           #+#    #+#             */
/*   Updated: 2024/09/24 09:14:07 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

char	*ft_strdup(const char *s)
{
	char	*string;
	int		length;

	string = malloc(ft_strlen(s) + 1);
	length = 0;
	if (string == NULL)
		return (NULL);
	while (s[length] != '\0')
	{
		string[length] = s[length];
		length++;
	}
	string[length] = '\0';
	return (string);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		length;
	int		j;

	length = 0;
	j = 0;
	string = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (string == NULL)
		return (NULL);
	while (s1[length] != '\0')
	{
		string[length] = s1[length];
		length++;
	}
	while (s2[j] != '\0')
	{
		string[length + j] = s2[j];
		j++;
	}
	string[j + length] = '\0';
	return (string);
}
