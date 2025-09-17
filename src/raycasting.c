/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:15:56 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/17 17:44:45 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	calc_dist(t_cub *cub, float x, float y, float angle)
{
	float	dx;
	float	dy;
	float	dist;

	dx = x - cub->game->xp_pos * TILE;
	dy = y - cub->game->yp_pos * TILE;
	dist = sqrtf(dx * dx + dy * dy);
	dist *= cosf(angle - atan2f(cub->game->dir_y, cub->game->dir_x));
	return (dist);
}

void	draw_ray(t_cub *cub, float angle, float *dist_array, int col)
{
	float	x;
	float	y;
	int		px;
	int		py;

	x = cub->game->xp_pos * TILE;
	y = cub->game->yp_pos * TILE;
	while (1)
	{
		px = (int)(x + 0.5f);
		py = (int)(y + 0.5f);
		if (px < 0 || px >= WIDTH || py < 0 || py >= HEIGHT)
			break ;
		if (cub->game->map[py / TILE][px / TILE] == '1')
		{
			dist_array[col] = calc_dist(cub, x, y, angle);
			break ;
		}
		x += cosf(angle);
		y += sinf(angle);
	}
}

// void	draw_ray(t_cub *cub, float angle, float *dist_array, int col)
// {
// 	float	x = cub->game->xp_pos * TILE;
// 	float	y = cub->game->yp_pos * TILE;
// 	float	step_x = cosf(angle) * 0.05f; // small step to prevent skipping
// 	float	step_y = sinf(angle) * 0.05f;
// 	int		map_x;
// 	int		map_y;

// 	while (1)
// 	{
// 		map_x = (int)(x / TILE);
// 		map_y = (int)(y / TILE);

// 		if (map_x < 0 || map_x >= cub->game->map_width
// 			|| map_y < 0 || map_y >= cub->game->map_height)
// 			break ;
// 		if (cub->game->map[map_y][map_x] == '1')
// 		{
// 			cub->rays->x_end = x;
// 			cub->rays->y_end = y;

// 			// Determine vertical or horizontal hit
// 			if ((int)((x - step_x) / TILE) != map_x)
// 				cub->rays->hit_vertical = 1;
// 			else
// 				cub->rays->hit_vertical = 0;

// 			dist_array[col] = calc_dist(cub, x, y, angle);
// 			break ;
// 		}
// 		x += step_x;
// 		y += step_y;
// 	}
// }



void	cast_rays(t_cub *cub, float start, float step, float *dist)
{
	int		i;
	float	angle;

	i = 0;
	while (i < WIDTH)
	{
		angle = start + i * step;
		draw_ray(cub, angle, dist, i);
		i++;
	}
}

void	draw_walls(t_cub *cub, float *dist, float fov)
{
	int		i;
	float	line_h;
	int		begin;
	int		end;

	i = 0;
    colores_set(cub);
	while (i < WIDTH)
	{
		line_h = (TILE / dist[i]) * ((WIDTH / 2.0f) / tanf(fov / 2.0f));
		begin = (HEIGHT / 2) - (int)(line_h / 2);
		end = begin + (int)line_h;
		if (begin < 0)
			begin = 0;
		if (end >= HEIGHT)
			end = HEIGHT - 1;
        put_pixel(cub, i, begin, end);
		i++;
	}
}

int	ray(t_cub *cub)
{
	float	dist[WIDTH];
	float	fov;
	float	start;
	float	step;

	cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
	if (!cub->textures->pixel_ray)
		return (1);
	mlx_image_to_window(cub->game->mlx, cub->textures->pixel_ray, 0, 0);
	fov = 60.0f * M_PI / 180.0f;
	start = atan2f(cub->game->dir_y, cub->game->dir_x) - fov / 2.0f;
	step = fov / (float)WIDTH;
	cast_rays(cub, start, step, dist);
	draw_walls(cub, dist, fov);
	return (0);
}