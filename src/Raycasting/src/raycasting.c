/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:15:56 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/30 17:48:20 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
                cub->rays->hit_cell = '1'; // treat out-of-bounds as wall
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
	// if (!cub->textures->pixel_ray)
	// 	cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
	// if (!cub->textures->pixel_ray)
	// 	return (1);
	while (x < WIDTH)
	{
		cast_ray(cub, x);
		x++;
	}
	// mlx_image_to_window(cub->game->mlx, cub->textures->pixel_ray, 0, 0);
	return (0);
}

// float	calc_dist(t_cub *cub, float x, float y, float angle)
// {
// 	float	dx;
// 	float	dy;
// 	float	dist;

// 	dx = x - cub->game->xp_pos * TILE;
// 	dy = y - cub->game->yp_pos * TILE;
// 	dist = sqrtf(dx * dx + dy * dy);
// 	dist *= cosf(angle - atan2f(cub->game->dir_y, cub->game->dir_x));
// 	return (dist);
// }

// void draw_ray(t_cub *cub, float angle, float *dist_array, float *hit_x, float *hit_y, int col)
// {
//     float x = cub->game->xp_pos * TILE;
//     float y = cub->game->yp_pos * TILE;
//     int px, py;

//     while (1)
//     {
//         px = (int)(x + 0.5f);
//         py = (int)(y + 0.5f);
//         if (px < 0 || px >= WIDTH || py < 0 || py >= HEIGHT)
//             break ;
//         if (cub->game->map[py / TILE][px / TILE] == '1')
//         {
//             dist_array[col] = calc_dist(cub, x, y, angle);
//             hit_x[col] = x / TILE; // world space
//             hit_y[col] = y / TILE; // world space
//             break ;
//         }
//         x += cosf(angle);
//         y += sinf(angle);
//     }
// }


// void cast_rays(t_cub *cub, float start, float step, float *dist, float *hit_x, float *hit_y)
// {
//     for (int i = 0; i < WIDTH; i++)
//         draw_ray(cub, start + i * step, dist, hit_x, hit_y, i);
// }


// // void	draw_walls(t_cub *cub, float *dist, float fov)
// // {
// // 	int		i;
// // 	float	line_h;
// // 	int		begin;
// // 	int		end;

// // 	i = 0;
// //     colores_set(cub);
// // 	while (i < WIDTH)
// // 	{
// // 		line_h = (TILE / dist[i]) * ((WIDTH / 2.0f) / tanf(fov / 2.0f));
// // 		begin = (HEIGHT / 2) - (int)(line_h / 2);
// // 		end = begin + (int)line_h;
// // 		if (begin < 0)
// // 			begin = 0;
// // 		if (end >= HEIGHT)
// // 			end = HEIGHT - 1;
// //         put_pixel(cub, i, begin, end);
// // 		i++;
// // 	}
// // }

// void draw_walls(t_cub *cub, float *dist, float fov, float *ray_hit_x, float *ray_hit_y)
// {
//     int i;
//     float line_h;
//     int begin, end;
//     int tex_x;
//     mlx_texture_t *tex;

//     colores_set(cub);
//     i = 0;
//     while (i < WIDTH)
//     {
//         // Wall height
//         line_h = (TILE / dist[i]) * ((WIDTH / 2.0f) / tanf(fov / 2.0f));
//         begin = (HEIGHT / 2) - (int)(line_h / 2);
//         end = begin + (int)line_h;
//         if (begin < 0) begin = 0;
//         if (end >= HEIGHT) end = HEIGHT - 1;

//         // Choose texture based on wall direction
//         if (fabs(ray_hit_x[i] - (int)ray_hit_x[i]) > fabs(ray_hit_y[i] - (int)ray_hit_y[i]))
//             tex = (ray_hit_x[i] > cub->game->xp_pos) ? cub->textures->east : cub->textures->west;
//         else
//             tex = (ray_hit_y[i] > cub->game->yp_pos) ? cub->textures->south : cub->textures->north;

//         // Compute tex_x from hit position
//         if (tex == cub->textures->north || tex == cub->textures->south)
//             tex_x = (int)(ray_hit_x[i] * tex->width) % tex->width;
//         else
//             tex_x = (int)(ray_hit_y[i] * tex->width) % tex->width;

//         put_wall_pixel(cub, i, begin, end, tex_x, tex);
//         i++;
//     }
// }

// // void cast_rays(t_cub *cub, float start, float step, float *dist, float *hit_x, float *hit_y)
// // {
// //     for (int i = 0; i < WIDTH; i++)
// //         draw_ray(cub, start + i * step, dist, hit_x, hit_y, i);
// // }


// int ray(t_cub *cub)
// {
//     float dist[WIDTH];
//     float ray_hit_x[WIDTH];
//     float ray_hit_y[WIDTH];
//     float fov = 60.0f * M_PI / 180.0f;
//     float start = atan2f(cub->game->dir_y, cub->game->dir_x) - fov / 2.0f;
//     float step = fov / (float)WIDTH;

//     cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
//     if (!cub->textures->pixel_ray)
//         return (1);
//     mlx_image_to_window(cub->game->mlx, cub->textures->pixel_ray, 0, 0);

//     cast_rays(cub, start, step, dist, ray_hit_x, ray_hit_y);
//     draw_walls(cub, dist, fov, ray_hit_x, ray_hit_y);
//     return 0;
// }