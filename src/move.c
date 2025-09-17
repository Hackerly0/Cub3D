/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:50:52 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/17 14:51:38 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void rotate_player(t_cub *cub, float theta)
{
    float old_dir_x;
    old_dir_x = cub->game->dir_x;
    cub->game->dir_x = cub->game->dir_x * cos(theta) - cub->game->dir_y * sin(theta);
    cub->game->dir_y = old_dir_x * sin(theta) + cub->game->dir_y * cos(theta);

    // 2️⃣ تدوير مستوى الكاميرا (plane_x, plane_y) إذا تستخدم raycasting
    // float old_plane_x = cub->game->plane_x;
    // cub->game->plane_x = cub->game->plane_x * cos(theta) - cub->game->plane_y * sin(theta);
    // cub->game->plane_y = old_plane_x * sin(theta) + cub->game->plane_y * cos(theta);
}

void move_up_donw(t_cub *cub, char type)
{
    if (type == 'W')
    {
        cub->game->xp_pos += cub->game->dir_x * 0.2f;
        cub->game->yp_pos += cub->game->dir_y * 0.2f;
        if (cub->game->map[(int)cub->game->yp_pos][(int)cub->game->xp_pos] == '1')
        {
            cub->game->xp_pos -= cub->game->dir_x * 0.2f;
            cub->game->yp_pos -= cub->game->dir_y * 0.2f;
        }
    }
    if (type == 'S')
    {
        cub->game->xp_pos -= cub->game->dir_x * 0.2f;
        cub->game->yp_pos -= cub->game->dir_y * 0.2f;
        if (cub->game->map[(int)cub->game->yp_pos][(int)cub->game->xp_pos] == '1')
        {
            cub->game->xp_pos += cub->game->dir_x * 0.2f;
            cub->game->yp_pos += cub->game->dir_y * 0.2f;
        }   
    }
}

void    move_left_rigth(t_cub *cub, char type)
{
    if (type == 'A')
    {
        cub->game->xp_pos -= 0.3;
        if (cub->game->map[(int)cub->game->yp_pos][(int)cub->game->xp_pos] == '1')
            cub->game->xp_pos += 0.3;
    }
    if (type == 'D')
    {
        cub->game->xp_pos += 0.3;
        if (cub->game->map[(int)cub->game->yp_pos][(int)cub->game->xp_pos] == '1')
            cub->game->xp_pos -= 0.3;
    }
}

void my_keyhook(mlx_key_data_t keydata, void *structs)
{
    t_cub *cub;
    
    cub = (t_cub *)structs;
    if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        rotate_player(cub, -0.05f);
    if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        rotate_player(cub, 0.05f);
    if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        move_up_donw(cub, 'W');
    if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        move_up_donw(cub, 'S');
    if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        move_left_rigth(cub, 'A');
    if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        move_left_rigth(cub, 'D');
    if (cub->textures->pixel_ray)
        mlx_delete_image(cub->game->mlx, cub->textures->pixel_ray);
    if (cub->textures->player)
        mlx_delete_image(cub->game->mlx, cub->textures->player);
    // player(cub->game, cub);
    ray(cub);
}