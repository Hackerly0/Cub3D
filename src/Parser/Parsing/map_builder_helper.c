/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:51:23 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/14 21:52:26 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_len(char **map)
{
	int	len;

	len = 0;
	if (!map)
		return (0);
	while (map[len])
		len++;
	return (len);
}

int	copy_old(char **dst, char **src)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			ft_free(dst, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	append_new(char **dst, int j, const char *s)
{
	dst[j] = ft_strdup(s);
	if (!dst[j])
	{
		ft_free(dst, j);
		return (1);
	}
	dst[j + 1] = NULL;
	return (0);
}

int	first_insert(t_vars *v, const char *s)
{
	char	**temp;

	temp = malloc(sizeof(char *) * 2);
	if (!temp)
		return (1);
	temp[0] = ft_strdup(s);
	if (!temp[0])
	{
		free(temp);
		return (1);
	}
	temp[1] = NULL;
	v->map = temp;
	v->width = (int)ft_strlen(s);
	v->height = 1;
	return (0);
}
