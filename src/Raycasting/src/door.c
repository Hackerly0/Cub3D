/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:25:52 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/01 19:03:13 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

