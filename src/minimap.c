/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:53:15 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/28 23:33:56 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_ray_minimap(t_cub *cub, float angle)
{
	float	x;
	float	y;
	int		px;
	int		py;

	x = cub->game->xp_pos * TILE * MINIMAP_SCALE;
	y = cub->game->yp_pos * TILE * MINIMAP_SCALE;
	while (1)
	{
		px = (int)(x + 0.5f);
		py = (int)(y + 0.5f);
		if (px < 0 || px >= WIDTH || py < 0 || py >= HEIGHT)
			break ;
		mlx_put_pixel(cub->textures->pixel_ray, px, py, 0xFF0000FF);

		if (cub->game->map[(int)(py / (TILE * MINIMAP_SCALE))][(int)(px / (TILE * MINIMAP_SCALE))] == '1')
        {
            
			break ;
        }
		x += cosf(angle);
		y += sinf(angle);
	}
}

int	ray_minimap(t_cub *cub)
{
	int		i;
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
	i = 0;
	while (i < WIDTH)
		draw_ray_minimap(cub, start + i++ * step);
    
	return (0);
}
// int player_minimap(t_cub *cub)
// {
//     int i;
//     int j;

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
//     return (0);
// }

// int draw_minimap(t_cub *cub)
// {
//     uint32_t color;
//     int i;
//     int j;
//     int x;
//     int y;

//     i = 0;
//     while (i < cub->game->map_height)
//     {
//         j = 0;
//         while (j < cub->game->map_width)
//         {
//             if (cub->game->map[i][j] == '1')
//                 color = 0xFFFFFFFF;
//             else if (cub->game->map[i][j] == '0')
//                 color = 0x000000FF;
//             x = 0;
//             while (x < TILE * MINIMAP_SCALE)
//             {
//                 y = 0;
//                 while (y < TILE * MINIMAP_SCALE)
//                 {
//                     mlx_put_pixel(cub->textures->wall, j * TILE * MINIMAP_SCALE + x, i * TILE * MINIMAP_SCALE + y, color);
//                     y++;
//                 }
//                 x++;
//             }
//             j++;
//         }
//         i++;
//     }
//     return 0;
// }

float calculate_minimap_scale(t_cub *cub)
{
    float scale_x, scale_y, final_scale;
    int max_minimap_width = WIDTH / 4;   
    int max_minimap_height = HEIGHT / 4; 
    scale_x = (float)max_minimap_width / (cub->game->map_width * TILE);
    scale_y = (float)max_minimap_height / (cub->game->map_height * TILE);
    
    final_scale = (scale_x < scale_y) ? scale_x : scale_y;
    
    if (final_scale < 0.1f)
        final_scale = 0.1f;
    if (final_scale > 2.0f)
        final_scale = 2.0f;
        
    return final_scale;
}

int player_minimap(t_cub *cub, float minimap_scale)
{
    int i;
    int j;
    int player_size = (int)(P_SIZE * minimap_scale);

    i = 0;
    while (i < player_size)
    {
        j = 0;
        while (j < player_size)
        {
            mlx_put_pixel(cub->textures->player, j, i, 0x00FF00FF);
            j++;
        }
        i++;
    }
    return (0);
}

int draw_minimap(t_cub *cub, float minimap_scale)
{
    uint32_t color;
    int i;
    int j;
    int x;
    int y;
    int scaled_tile_size = (int)(TILE * minimap_scale);

    i = 0;
    while (i < cub->game->map_height)
    {
        j = 0;
        while (j < cub->game->map_width)
        {
            if (cub->game->map[i][j] == '1')
                color = 0xFFFFFFFF;
            else if (cub->game->map[i][j] == '0')
                color = 0x000000FF;
            else
            {
                j++;
                continue;
            }
                
            x = 0;
            while (x < scaled_tile_size)
            {
                y = 0;
                while (y < scaled_tile_size)
                {
                    int pixel_x = j * scaled_tile_size + x;
                    int pixel_y = i * scaled_tile_size + y;
                    
                    if (pixel_x < (int)cub->textures->wall->width && 
                        pixel_y < (int)cub->textures->wall->height)
                    {
                        mlx_put_pixel(cub->textures->wall, pixel_x, pixel_y, color);
                    }
                    y++;
                }
                x++;
            }
            j++;
        }
        i++;
    }
    return 0;
}

int init_image_adaptive(t_cub *cub, float minimap_scale)
{
    int minimap_width = (int)(cub->game->map_width * TILE * minimap_scale);
    int minimap_height = (int)(cub->game->map_height * TILE * minimap_scale);
    int player_size = (int)(P_SIZE * minimap_scale);
    
    cub->textures->wall = mlx_new_image(cub->game->mlx, minimap_width, minimap_height);
    if (!cub->textures->wall)
        return (1);
        
    cub->textures->player = mlx_new_image(cub->game->mlx, player_size, player_size);
    if (!cub->textures->player)
        return (1);
        
    cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
    if (!cub->textures->pixel_ray)
        return (1);
        
    return (0);
}



void keyhook(void *param)
{
    t_cub *cub;
    float minimap_scale;
    
    cub = (t_cub *)param;
    minimap_scale = cub->game->minimap_scale;
    
    if (!cub->textures->pixel_ray)
        cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
    handle_movement_keys(cub);
    ray(cub);
    
    if (cub->textures->player && cub->textures->player->instances)
    {
        cub->textures->player->instances[0].x = 
            (int)(cub->game->xp_pos * TILE * minimap_scale) - (P_SIZE * minimap_scale)/2;
        cub->textures->player->instances[0].y = 
            (int)(cub->game->yp_pos * TILE * minimap_scale) - (P_SIZE * minimap_scale)/2;
    }
}
// if (cub->game->map[i][j] == '1')
//             {
//                 int x = 0;
//                 while (x < TILE * MINIMAP_SCALE)
//                 {
//                     int y = 0;
//                     while (y < TILE * MINIMAP_SCALE)
//                     {
//                         mlx_put_pixel(cub->textures->pixel_ray, j * TILE * MINIMAP_SCALE + x, i * TILE * MINIMAP_SCALE + y, 0xFFFFFFFF);
//                         y++;
//                     }
//                     x++;
//                 }
//             }
//             else if (cub->game->map[i][j] == '0')
//             {
//                 int x = 0;
//                 while (x < TILE * MINIMAP_SCALE)
//                 {
//                     int y = 0;
//                     while (y < TILE * MINIMAP_SCALE)
//                     {
//                         mlx_put_pixel(cub->textures->pixel_ray, j * TILE * MINIMAP_SCALE + x, i * TILE * MINIMAP_SCALE + y, 0x00000000);
//                         y++;
//                     }
//                     x++;
//                 }
                
//             }