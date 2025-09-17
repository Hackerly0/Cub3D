/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:53:15 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/17 15:25:29 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	draw_ray_minimap(t_cub *cub, float angle)
// {
// 	float	x;
// 	float	y;
// 	int		px;
// 	int		py;

// 	x = cub->game->xp_pos * TILE;
// 	y = cub->game->yp_pos * TILE;
// 	while (1)
// 	{
// 		px = (int)(x + 0.5f);
// 		py = (int)(y + 0.5f);
// 		if (px < 0 || px >= WIDTH || py < 0 || py >= HEIGHT)
// 			break ;
// 		mlx_put_pixel(cub->textures->pixel_ray, px, py, 0xFF0000FF);

// 		if (cub->game->map[py / TILE][px / TILE] == '1')
//         {
            
// 			break ;
//         }
// 		x += cosf(angle);
// 		y += sinf(angle);
// 	}
// }

// int	ray_minimap(t_cub *cub)
// {
// 	int		i;
// 	float	fov;
// 	float	start;
// 	float	step;

// 	cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
// 	if (!cub->textures->pixel_ray)
// 		return (1);
// 	mlx_image_to_window(cub->game->mlx, cub->textures->pixel_ray, 0, 0);
// 	fov = 60.0f * M_PI / 180.0f;
// 	start = atan2f(cub->game->dir_y, cub->game->dir_x) - fov / 2.0f;
// 	step = fov / (float)WIDTH;
// 	i = 0;
// 	while (i < WIDTH)
// 		draw_ray_minimap(cub, start + i++ * step);
    
// 	return (0);
// }

// int    player_minimap(t_game *game, t_cub *cub)
// {
//     int i;
//     int j;
//     int px;
//     int py;

//     cub->textures->player = mlx_new_image(game->mlx, P_SIZE, P_SIZE);
//     if (!cub->textures->player)
//         return (1);
//     i = 0;
//     while (i < P_SIZE)
//     {
//         j = 0;
//         while (j < P_SIZE)
//         {
//             mlx_put_pixel(cub->textures->player, j, i, 0x00FF00FF);
//             j++;
//         }
//         i++;
//     }
//     px = (int)(game->xp_pos * TILE);
//     py = (int)(game->yp_pos * TILE);
//     mlx_image_to_window(game->mlx, cub->textures->player, px, py);
//     return (0);
// }

// int    draw_minimap(t_cub *cub)
// {
//     int i;
//     int j;
    
//     cub->textures->wall = mlx_new_image(cub->game->mlx, TILE, TILE);
//     if (!cub->textures->wall)
//         return (1);
//     memset(cub->textures->wall->pixels, 255, cub->textures->wall->width * cub->textures->wall->height * BPP);
//     i = 0;
//     while (i < cub->game->map_height)
//     {
//         j = 0;
//         while (j < cub->game->map_width)
//         {
//             if (cub->game->map[i][j] == '1')
//                 mlx_image_to_window(cub->game->mlx, cub->textures->wall, j * TILE, i * TILE);
//             j++;
//         }
//         i++;
//     }
//     return (0);
// }
