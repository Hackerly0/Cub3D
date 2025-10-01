/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:25:52 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/01 21:09:16 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void toggle_nearest_door(t_cub *cub)
{
    int check_x;
	int check_y;
    float check_dist;

    check_dist = 1.5f; 
    check_x = (int)(cub->game->xp_pos + cub->game->dir_x * check_dist);
    check_y = (int)(cub->game->yp_pos + cub->game->dir_y * check_dist);
    if (cub->game->map[check_y][check_x] == 'D')
        if (cub->game->door_state[check_y][check_x] == '1')
            cub->game->door_state[check_y][check_x] = '0';
}

void init_door_states(t_game *game)
{
    int y;
    int x;
    
    game->door_state = malloc(game->map_height * sizeof(char*));
    if (!game->door_state)
        return;
    
    y = 0;
    while (y < game->map_height)
    {
        game->door_state[y] = malloc(game->map_width + 1);
        if (!game->door_state[y])
            return;
        x = 0;
        while (x < game->map_width)
        {
            if (game->map[y][x] == 'D')
                game->door_state[y][x] = '1';
            else
                game->door_state[y][x] = '0';
            x++;
        }
        game->door_state[y][game->map_width] = '\0';
        y++;
    }
}

