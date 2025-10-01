/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:50:52 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/01 20:04:27 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void rotate_player(t_cub *cub, float angle)
{
	float	old_dir_x;
	float	old_plane_x;
	float	cos_angle;
	float	sin_angle;

	old_dir_x = cub->game->dir_x;
	old_plane_x = cub->game->plane_x;
	cos_angle = cos(angle);
	sin_angle = sin(angle);
    cub->game->dir_x = cub->game->dir_x * cos_angle - cub->game->dir_y * sin_angle;
    cub->game->dir_y = old_dir_x * sin_angle + cub->game->dir_y * cos_angle;
    cub->game->plane_x = cub->game->plane_x * cos_angle - cub->game->plane_y * sin_angle;
    cub->game->plane_y = old_plane_x * sin_angle + cub->game->plane_y * cos_angle;
}

void	move_player(t_cub *cub, float move_x, float move_y)
{
	float	new_x;
	float	new_y;
	float	margin;
	float	check_x;
	float	check_y;

	new_x = cub->game->xp_pos + move_x;
	new_y = cub->game->yp_pos + move_y;
	margin = 0.1f;
	if (move_x > 0)
		check_x = new_x + margin;
	else
		check_x = new_x - margin;
	if (is_valid_position(cub, check_x, cub->game->yp_pos))
		cub->game->xp_pos = new_x;
	if (move_y > 0)
		check_y = new_y + margin;
	else
		check_y = new_y - margin;
	if (is_valid_position(cub, cub->game->xp_pos, check_y))
		cub->game->yp_pos = new_y;
}

void	cursor(double xpos, double ypos, void *param)
{
	t_cub	*cub;
    double delta_x;
	static double last_x = -1;
    
	cub = (t_cub *)param;
    (void)ypos;
	if (last_x < 0)
		last_x = xpos;
	delta_x = xpos - last_x;
	if (delta_x != 0)
		rotate_player(cub, delta_x * 0.002f);
	last_x = xpos;
}

void handle_movement_keys(t_cub *cub)
{
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_SPACE))
		toggle_nearest_door(cub);
    if (mlx_is_key_down(cub->game->mlx, MLX_KEY_W))
        move_player(cub, cub->game->dir_x * MOVE_SPEED, cub->game->dir_y * MOVE_SPEED);
    if (mlx_is_key_down(cub->game->mlx, MLX_KEY_S))
        move_player(cub, -cub->game->dir_x * MOVE_SPEED, -cub->game->dir_y * MOVE_SPEED);
    if (mlx_is_key_down(cub->game->mlx, MLX_KEY_A))
        move_player(cub, cub->game->dir_y * MOVE_SPEED, -cub->game->dir_x * MOVE_SPEED);
    if (mlx_is_key_down(cub->game->mlx, MLX_KEY_D))
        move_player(cub, -cub->game->dir_y * MOVE_SPEED, cub->game->dir_x * MOVE_SPEED);
    if (mlx_is_key_down(cub->game->mlx, MLX_KEY_LEFT))
        rotate_player(cub, -ROT_SPEED);
    if (mlx_is_key_down(cub->game->mlx, MLX_KEY_RIGHT))
        rotate_player(cub, ROT_SPEED);
    if (mlx_is_key_down(cub->game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(cub->game->mlx);
}

void keyhook(void *param)
{
    t_cub *cub;

    cub = (t_cub *)param;
    if (!cub->textures->pixel_ray)
        cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
    handle_movement_keys(cub);
    ray(cub);
	draw_minimap(cub);
	if (cub->textures->player && cub->textures->player->instances)
    {
        cub->textures->player->instances[0].x = (int)(cub->game->xp_pos * cub->game->minimap_scale);
        cub->textures->player->instances[0].y = (int)(cub->game->yp_pos * cub->game->minimap_scale);
    }
}