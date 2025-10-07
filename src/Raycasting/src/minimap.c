/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:53:15 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/05 17:58:26 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

uint32_t minimap_color(t_cub *cub, int i, int j)
{
    uint32_t color;

    color = 0x00000000;
    if (cub->game->map[i][j] == '1')
        color = 0xFFFFFFFF;
    else if (cub->game->map[i][j] == '0')
        color = 0x000000FF;
    else if (cub->game->map[i][j] == 'D')
    {
        if (cub->game->door_state[i][j] == '1')
            color = 0xFF0000FF;
        else
            color = 0x00FF00FF;
    }
    return (color);
}

void	draw_minimap_tile(t_cub *cub, int map_x, int map_y, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	while (x < cub->game->minimap_scale)
	{
		y = 0;
		while (y < cub->game->minimap_scale)
		{
			mlx_put_pixel(cub->textures->wall,
				map_x * cub->game->minimap_scale + x,
				map_y * cub->game->minimap_scale + y,
				color);
			y++;
		}
		x++;
	}
}

int	draw_minimap(t_cub *cub)
{
	int			i;
	int			j;
	uint32_t	color;

	i = 0;
	while (i < cub->game->map_height)
	{
		j = 0;
		while (j < cub->game->map_width)
		{
			color = minimap_color(cub, i, j);
			draw_minimap_tile(cub, j, i, color);
			j++;
		}
		i++;
	}
	return (0);
}
