/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:02:47 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/17 18:51:33 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static uint32_t rgb_to_hex(int r, int g, int b)
{
    return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) |
           ((b & 0xFF) << 8)  | 0xFF; // Alpha = 255
}

void    colores_set(t_cub *cub)
{
cub->colors->ceil[0] = 135; // R
cub->colors->ceil[1] = 206; // G
cub->colors->ceil[2] = 235; // B

cub->colors->floor[0] = 34;
cub->colors->floor[1] = 139;
cub->colors->floor[2] = 34;
    cub->colors->ceil_col = rgb_to_hex(cub->colors->ceil[0], cub->colors->ceil[1], cub->colors->ceil[2]);
	cub->colors->floor_col = rgb_to_hex(cub->colors->floor[0], cub->colors->floor[1], cub->colors->floor[2]);
}

void    put_pixel(t_cub *cub, int i, int begin, int end)
{
    int y;
    // mlx_texture_t *t;
    // int tex_y;
    // int tex_x;
    // uint32_t color;

    // if (wall_dir[0] == 'N') 
    //     t = cub->textures->walls->north;
    // else if (wall_dir[0] == 'S') 
    //     t = cub->textures->walls->south;
    // else if (wall_dir[0] == 'E') 
    //     t = cub->textures->walls->east;
    // else 
    //     t = cub->textures->walls->west;

    y = 0;
    while (y < begin)
		mlx_put_pixel(cub->textures->pixel_ray, i, y++, cub->colors->ceil_col);
	y = begin;
    // while (y < end)
    // {
    //     tex_y = (y - begin) * t->height / (end - begin);  // simple vertical scaling
    //     tex_x = i * t->width / WIDTH;                     // simple horizontal scaling
    //     color = t->pixels[tex_y * t->width + tex_x];
    //     mlx_put_pixel(cub->textures->pixel_ray, i, y, color);
    //     y++;
    // }
	while (y < end)
		mlx_put_pixel(cub->textures->pixel_ray, i, y++, 0xFF0000FF);
	y = end;
	while (y < HEIGHT)
		mlx_put_pixel(cub->textures->pixel_ray, i, y++, cub->colors->floor_col);
}

// void put_pixel(t_cub *cub, int i, int begin, int end)
// {
//     int y;
//     mlx_texture_t *t;
//     int tex_x;
//     int tex_y;
//     uint32_t color;

//     if (cub->rays->hit_vertical)
//     {
//         if (cub->rays->x_end > cub->game->xp_pos)
//             t = cub->textures->east;
//         else
//             t = cub->textures->west;
//     }
//     else
//     {
//         if (cub->rays->y_end > cub->game->yp_pos)
//             t = cub->textures->south;
//         else
//             t = cub->textures->north;
//     }
//     y = 0;
//     while (y < begin)
//         mlx_put_pixel(cub->textures->pixel_ray, i, y++, cub->colors->ceil_col);
//     y = begin;
//     while (y < end)
//     {
//         tex_y = (y - begin) * t->height / (end - begin);
//         tex_x = i * t->width / WIDTH;
//         color = t->pixels[tex_y * t->width + tex_x];
//         mlx_put_pixel(cub->textures->pixel_ray, i, y, color);
//         y++;
//     }
//     y = end;
//     while (y < HEIGHT)
//         mlx_put_pixel(cub->textures->pixel_ray, i, y++, cub->colors->floor_col);
// }
