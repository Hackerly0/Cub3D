/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:52:47 by hnisirat          #+#    #+#             */
/*   Updated: 2025/09/30 14:54:13 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_allowed(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	touches_void8(t_vars *v, int y, int x)
{
	int	dy;
	int	dx;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!(dy == 0 && dx == 0))
				if (is_void_or_oob(v, y + dy, x + dx))
					return (1);
			dx++;
		}
		dy++;
	}
	return (0);
}

int	validate_chars(t_vars *v)
{
	int	i;
	int	j;

	i = 0;
	while (i < v->height)
	{
		j = 0;
		while (j < v->width)
		{
			if (!is_allowed(v->map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	map_validation(t_vars *v)
{
	int	i;
	int	j;

	if (validate_chars(v))
		return (1);
	i = 0;
	while (i < v->height)
	{
		j = 0;
		while (j < v->width)
		{
			if (v->map[i][j] == '0' && touches_void8(v, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
