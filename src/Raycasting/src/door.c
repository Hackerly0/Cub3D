/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:25:52 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/06 18:21:00 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int correct_answer()
{
    return (0); // 50% chance of returning 0 or 1
}

void toggle_nearest_door(t_cub *cub)
{
    int check_x;
	int check_y;
    float check_dist;
    mlx_image_t *scery_img;
    
    scery_img = mlx_texture_to_image(cub->game->mlx, cub->textures->scery);
    check_dist = 1.5f; 
    check_x = (int)(cub->game->xp_pos + cub->game->dir_x * check_dist);
    check_y = (int)(cub->game->yp_pos + cub->game->dir_y * check_dist);
    if (cub->game->map[check_y][check_x] == 'D')
    {
        if (cub->game->door_state[check_y][check_x] == '1')
        {
            print_qa(grab_questions());
            if(correct_answer())
                cub->game->door_state[check_y][check_x] = '0';
            else
            {
                mlx_resize_image(scery_img, WIDTH, HEIGHT);
                mlx_image_to_window(cub->game->mlx, scery_img, 0, 0);
            }
        }
    }
}

void space_hook(mlx_key_data_t keydata, void* param)
{
    t_cub *cub = (t_cub *)param;

    if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
        toggle_nearest_door(cub);
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

