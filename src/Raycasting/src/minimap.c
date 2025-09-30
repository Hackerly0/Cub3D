/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:53:15 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/30 16:05:52 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	draw_ray_minimap(t_cub *cub, float angle)
// {
// 	float	x;
// 	float	y;
// 	int		px;
// 	int		py;

// 	x = cub->game->xp_pos * TILE * MINIMAP_SCALE;
// 	y = cub->game->yp_pos * TILE * MINIMAP_SCALE;
// 	while (1)
// 	{
// 		px = (int)(x + 0.5f);
// 		py = (int)(y + 0.5f);
// 		if (px < 0 || px >= WIDTH || py < 0 || py >= HEIGHT)
// 			break ;
// 		mlx_put_pixel(cub->textures->pixel_ray, px, py, 0xFF0000FF);

// 		if (cub->game->map[(int)(py / (TILE * MINIMAP_SCALE))][(int)(px / (TILE * MINIMAP_SCALE))] == '1')
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

void chosse_scale(t_cub *cub)
{
    if (cub->game->map_height > cub->game->map_width)
        cub->game->minimap_scale = 200 / cub->game->map_height;
    else
        cub->game->minimap_scale = 200 / cub->game->map_width;
}

int player_minimap(t_cub *cub)
{
    int i;
    int j;
    int player_size = (int)(P_SIZE * MINIMAP_SCALE);

    i = 0;
    while (i < player_size)
    {
        j = 0;
        while (j < player_size)
        {
            mlx_put_pixel(cub->textures->player, j, i, 0xFFFF00FF);
            j++;
        }
        i++;
    }
    return (0);
}

int draw_minimap(t_cub *cub)
{
    uint32_t color;
    int i;
    int j;
    int x;
    int y;

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
            else if (cub->game->map[i][j] == 'D')
            {
                if (cub->game->door_state[i][j] == '1')
                    color = 0xFF0000FF; // Red for closed doors
                else
                    color = 0x00FF00FF; // Green for open doors
            }
            x = 0;
            while (x < cub->game->minimap_scale)
            {
                y = 0;
                while (y < cub->game->minimap_scale)
                {
                    mlx_put_pixel(cub->textures->wall, j * cub->game->minimap_scale + x, i * cub->game->minimap_scale + y, color);
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
