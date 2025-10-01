/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:15:56 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/01 20:04:39 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_vars(t_cub *cub, int x, t_rays *ray)
{
	float	camera_x;

	camera_x = 2 * x / (float)WIDTH - 1;
	ray->ray_x = cub->game->dir_x + cub->game->plane_x * camera_x;
	ray->ray_y = cub->game->dir_y + cub->game->plane_y * camera_x;
	ray->map_x = (int)cub->game->xp_pos;
	ray->map_y = (int)cub->game->yp_pos;
	if (ray->ray_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1.0f / ray->ray_x);
	if (ray->ray_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0f / ray->ray_y);
}

void	init_steps(t_cub *cub, t_rays *ray)
{
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (cub->game->xp_pos - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0f - cub->game->xp_pos) * ray->delta_x;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (cub->game->yp_pos - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0f - cub->game->yp_pos) * ray->delta_y;
	}
}

void perform_dda(t_cub *cub)
{
    cub->rays->hit_cell = '0';
    while (1)
    {
        if (cub->rays->side_x < cub->rays->side_y)
            (cub->rays->side_x += cub->rays->delta_x,
             cub->rays->map_x += cub->rays->step_x,
             cub->rays->side = 0);
        else
            (cub->rays->side_y += cub->rays->delta_y,
             cub->rays->map_y += cub->rays->step_y,
             cub->rays->side = 1);

        if (cub->rays->map_x < 0 || cub->rays->map_x >= cub->game->map_width
         || cub->rays->map_y < 0 || cub->rays->map_y >= cub->game->map_height
         || cub->game->map[cub->rays->map_y][cub->rays->map_x] == '1'
         || (cub->game->map[cub->rays->map_y][cub->rays->map_x] == 'D'
             && cub->game->door_state[cub->rays->map_y][cub->rays->map_x] == '1'))
        {
            cub->rays->hit_cell = cub->game->map[cub->rays->map_y][cub->rays->map_x];
            if (cub->rays->map_x < 0 || cub->rays->map_x >= cub->game->map_width
             || cub->rays->map_y < 0 || cub->rays->map_y >= cub->game->map_height)
                cub->rays->hit_cell = '1';
            return;
        }
    }
}

void	cast_ray(t_cub *cub, int x)
{
	float	dist;

	init_ray_vars(cub, x, cub->rays);
	init_steps(cub, cub->rays);
	perform_dda(cub);
	dist = get_distance(cub);
	draw_column(cub, x, dist);
}

int	ray(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(cub, x);
		x++;
	}
	return (0);
}
