/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:25:52 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/29 14:26:21 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
            // '1' = closed, '0' = open
            if (game->map[y][x] == 'D')
                game->door_state[y][x] = '1';  // Closed by default
            else
                game->door_state[y][x] = '0';
            x++;
        }
        game->door_state[y][game->map_width] = '\0';
        y++;
    }
}

