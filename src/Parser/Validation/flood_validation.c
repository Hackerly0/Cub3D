/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:52:54 by hnisirat          #+#    #+#             */
/*   Updated: 2025/09/30 14:52:55 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	ff_visit_neighbors(char **map, int x, int y, t_vars *var)
{
	if (flood_fill_recursive(map, x, y + 1, var))
		return (1);
	if (flood_fill_recursive(map, x + 1, y, var))
		return (1);
	if (flood_fill_recursive(map, x, y - 1, var))
		return (1);
	if (flood_fill_recursive(map, x - 1, y, var))
		return (1);
	return (0);
}

int	flood_fill_recursive(char **map, int x, int y, t_vars *var)
{
	char	current;

	if ((x < 0 || x >= var->width) || (y < 0 || y >= var->height))
		return (1);
	current = map[y][x];
	if (current == '1' || current == 'v')
		return (0);
	if (current == ' ')
		return (1);
	if (is_walkable(map[y][x]))
	{
		map[y][x] = 'v';
		if (ff_visit_neighbors(map, x, y, var))
			return (1);
	}
	return (0);
}

int	warp_flood_fill(t_vars *var)
{
	char	**new_map;
	int		result;

	new_map = copy_map(var->map, var->height);
	if (!new_map)
		return (1);
	result = flood_fill_recursive(
			new_map,
			(int)var->player.x,
			(int)var->player.y,
			var);
	ft_free(new_map, -1);
	return (result);
}

int	is_void_or_oob(t_vars *v, int y, int x)
{
	if (y < 0 || y >= v->height || x < 0 || x >= v->width)
		return (1);
	return (v->map[y][x] == ' ');
}
