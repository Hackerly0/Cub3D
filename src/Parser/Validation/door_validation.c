/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:15:00 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/09 19:19:54 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	count_doors(t_vars *v)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < v->height)
	{
		x = 0;
		while (x < v->width)
		{
			if (v->map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int	count_visited_doors(char **visited_map, t_vars *v)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (y < v->height)
	{
		x = 0;
		while (x < v->width)
		{
			if (v->map[y][x] == 'D' && visited_map[y][x] == 'v')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static int	flood_fill_with_doors(char **map, int x, int y, t_vars *var)
{
	char	current;

	if ((x < 0 || x >= var->width) || (y < 0 || y >= var->height))
		return (1);
	current = map[y][x];
	if (current == '1' || current == 'v')
		return (0);
	if (current == ' ')
		return (1);
	if (is_walkable(var->map[y][x]) || var->map[y][x] == 'D')
	{
		map[y][x] = 'v';
		if (flood_fill_with_doors(map, x, y + 1, var))
			return (1);
		if (flood_fill_with_doors(map, x + 1, y, var))
			return (1);
		if (flood_fill_with_doors(map, x, y - 1, var))
			return (1);
		if (flood_fill_with_doors(map, x - 1, y, var))
			return (1);
	}
	return (0);
}

int	validate_door_accessibility(t_vars *v)
{
	char	**visited_map;
	int		total_doors;
	int		accessible_doors;

	total_doors = count_doors(v);
	if (total_doors == 0)
		return (0);
	visited_map = copy_map(v->map, v->height);
	if (!visited_map)
		return (1);
	flood_fill_with_doors(visited_map,
		(int)v->player.x,
		(int)v->player.y,
		v);
	accessible_doors = count_visited_doors(visited_map, v);
	ft_free(visited_map, -1);
	if (accessible_doors != total_doors)
	{
		printf("Error\nSome doors are not accessible by player\n");
		printf("Total doors: %d, Accessible: %d\n",
			total_doors, accessible_doors);
		return (1);
	}
	return (0);
}
