/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: you                                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 00:00:00 by you               #+#    #+#             */
/*   Updated: 2025/09/12 00:00:00 by you              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "../include/cub3d.h"

static int	ft_rowlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_fill_spaces(char *dst, int start, int end)
{
	while (start < end)
	{
		dst[start] = ' ';
		start++;
	}
}

static int	ft_pad_one_row(char **row_ptr, int width)
{
	char	*old;
	char	*new;
	int		len;
	int		i;

	old = *row_ptr;
	len = ft_rowlen(old);
	if (len >= width)
		return (0);
	new = (char *)malloc((size_t)width + 1);
	if (!new)
		return (1);
	i = 0;
	while (i < len)
	{
		new[i] = old[i];
		i++;
	}
	ft_fill_spaces(new, len, width);
	new[width] = '\0';
	free(old);
	*row_ptr = new;
	return (0);
}

/* return 0 on success, 1 on alloc error */
int	pad_map_rect(t_vars *v)
{
	int	y;
	int	maxw;

	if (!v || !v->map)
		return (0);
	maxw = 0;
	y = 0;
	while (v->map[y])
	{
		if (ft_rowlen(v->map[y]) > maxw)
			maxw = ft_rowlen(v->map[y]);
		y++;
	}
	v->height = y;
	if (v->width < maxw)
		v->width = maxw;
	y = 0;
	while (v->map[y])
	{
		if (ft_pad_one_row(&v->map[y], v->width))
			return (1);
		y++;
	}
	return (0);
}
