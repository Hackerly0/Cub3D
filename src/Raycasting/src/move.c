/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:50:52 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/01 19:03:30 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void rotate_player(t_cub *cub, float theta)
// {
//     float old_dir_x = cub->game->dir_x;
//     float old_plane_x = cub->game->plane_x;
    
//     cub->game->dir_x = cub->game->dir_x * cos(theta) - cub->game->dir_y * sin(theta);
//     cub->game->dir_y = old_dir_x * sin(theta) + cub->game->dir_y * cos(theta);
    
//     cub->game->plane_x = cub->game->plane_x * cos(theta) - cub->game->plane_y * sin(theta);
//     cub->game->plane_y = old_plane_x * sin(theta) + cub->game->plane_y * cos(theta);
// }

// // Simplified collision detection
// int check_collision(t_cub *cub, float new_x, float new_y)
// {
//     float margin = 0.2f;
    
//     // Check the four corners around the player
//     if ((int)(new_x - margin) < 0 || (int)(new_x + margin) >= cub->game->map_width ||
//         (int)(new_y - margin) < 0 || (int)(new_y + margin) >= cub->game->map_height)
//         return 1;
        
//     if (cub->game->map[(int)(new_y - margin)][(int)(new_x - margin)] == '1' ||
//         cub->game->map[(int)(new_y - margin)][(int)(new_x + margin)] == '1' ||
//         cub->game->map[(int)(new_y + margin)][(int)(new_x - margin)] == '1' ||
//         cub->game->map[(int)(new_y + margin)][(int)(new_x + margin)] == '1')
//         return 1;
        
//     return 0;
// }

// // void move_up_donw(t_cub *cub, char type)
// // {
// //     if (type == 'W')
// //     {
// //         // Calculate new position
// //         float new_x = cub->game->xp_pos + cub->game->dir_x * 0.2f;
// //         float new_y = cub->game->yp_pos + cub->game->dir_y * 0.2f;
        
// //         // Check collision BEFORE moving
// //         if (!check_collision(cub, new_x * TILE, new_y * TILE))
// //         {
// //             // No collision - safe to move
// //             cub->game->xp_pos = new_x;
// //             cub->game->yp_pos = new_y;
// //         }
// //         // If there IS collision, don't move at all
// //     }
// //     else if (type == 'S')
// //     {
// //         float new_x = cub->game->xp_pos - cub->game->dir_x * 0.2f;
// //         float new_y = cub->game->yp_pos - cub->game->dir_y * 0.2f;
        
// //         if (!check_collision(cub, new_x * TILE, new_y * TILE))
// //         {
// //             cub->game->xp_pos = new_x;
// //             cub->game->yp_pos = new_y;
// //         }
// //     }
// // }

// void move_up_donw(t_cub *cub, char type)
// {
//     if (type == 'W')
//     {
//         float new_x = cub->game->xp_pos + cub->game->dir_x * 0.1f;
//         float new_y = cub->game->yp_pos + cub->game->dir_y * 0.1f;
        
//         // Use the same collision check as move_left_right (without TILE multiplication)
//         if (!check_collision(cub, new_x, new_y))
//         {
//             cub->game->xp_pos = new_x;
//             cub->game->yp_pos = new_y;
//         }
//     }
//     else if (type == 'S')
//     {
//         float new_x = cub->game->xp_pos - cub->game->dir_x * 0.1f;
//         float new_y = cub->game->yp_pos - cub->game->dir_y * 0.1f;
        
//         if (!check_collision(cub, new_x, new_y))
//         {
//             cub->game->xp_pos = new_x;
//             cub->game->yp_pos = new_y;
//         }
//     }
// }

// // void move_up_donw(t_cub *cub, char type)
// // {
// //     if (type == 'W')
// //     {
// //         cub->game->xp_pos += cub->game->dir_x * 0.2f;
// //         cub->game->yp_pos += cub->game->dir_y * 0.2f;
// //         // if (cub->game->map[(int)cub->game->yp_pos][(int)cub->game->xp_pos] == '1')
// //         if (!check_collision(cub, cub->game->xp_pos, cub->game->yp_pos))
// //         {
// //             printf("anuthinggg\n");
// //             cub->game->xp_pos -= cub->game->dir_x * 0.2f;
// //             cub->game->yp_pos -= cub->game->dir_y * 0.2f;
// //         }
// //     }
// //     if (type == 'S')
// //     {
// //         cub->game->xp_pos -= cub->game->dir_x * 0.2f;
// //         cub->game->yp_pos -= cub->game->dir_y * 0.2f;
// //         if (cub->game->map[(int)cub->game->yp_pos][(int)cub->game->xp_pos] == '1')
// //         {
// //             cub->game->xp_pos += cub->game->dir_x * 0.2f;
// //             cub->game->yp_pos += cub->game->dir_y * 0.2f;
// //         }   
// //     }
// // }

// // void	move_left_right(t_cub *cub, char type)
// // {
// // 	if (type == 'A')
// // 	{
// // 		cub->game->xp_pos += cub->game->dir_y * 0.2f;
// // 		cub->game->yp_pos -= cub->game->dir_x * 0.2f;
// // 		if (cub->game->map[(int)cub->game->yp_pos][(int)cub->game->xp_pos] == '1')
// // 		{
// // 			cub->game->xp_pos -= cub->game->dir_y * 0.2f;
// // 			cub->game->yp_pos += cub->game->dir_x * 0.2f;
// // 		}
// // 	}
// // 	if (type == 'D')
// // 	{
// // 		cub->game->xp_pos -= cub->game->dir_y * 0.2f; //we use cub->game->dir_y here because when we rotate the facing dir 90 digree the x component become y component 
// // 		cub->game->yp_pos += cub->game->dir_x * 0.2f;
// // 		if (cub->game->map[(int)cub->game->yp_pos][(int)cub->game->xp_pos] == '1')
// // 		{
// // 			cub->game->xp_pos += cub->game->dir_y * 0.2f;
// // 			cub->game->yp_pos -= cub->game->dir_x * 0.2f;
// // 		}
// // 	}
// // }

// void move_left_right(t_cub *cub, char type)
// {
//     if (type == 'A')
//     {
//         float new_x = cub->game->xp_pos + cub->game->dir_y * 0.1f;  // Reduced from 0.2f
//         float new_y = cub->game->yp_pos - cub->game->dir_x * 0.1f;
        
//         // Remove TILE multiplication to match move_up_down
//         if (!check_collision(cub, new_x, new_y))
//         {
//             cub->game->xp_pos = new_x;
//             cub->game->yp_pos = new_y;
//         }
//     }
//     if (type == 'D')
//     {
//         float new_x = cub->game->xp_pos - cub->game->dir_y * 0.1f;
//         float new_y = cub->game->yp_pos + cub->game->dir_x * 0.1f;
        
//         if (!check_collision(cub, new_x, new_y))
//         {
//             cub->game->xp_pos = new_x;
//             cub->game->yp_pos = new_y;
//         }
//     }
// }

// void my_keyhook(mlx_key_data_t keydata, void *structs)
// {
//     t_cub *cub;
    
//     cub = (t_cub *)structs;
//     if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
//         rotate_player(cub, -0.05f);
//     if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
//         rotate_player(cub, 0.05f);
//     if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
//         move_up_donw(cub, 'W');
//     if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
//         move_up_donw(cub, 'S');
//     if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
//         move_left_right(cub, 'A');
//     if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
//         move_left_right(cub, 'D');
//     if (cub->textures->pixel_ray)
//         mlx_delete_image(cub->game->mlx, cub->textures->pixel_ray);
//     if (cub->textures->player)
//         mlx_delete_image(cub->game->mlx, cub->textures->player);
//     // player(cub->game, cub);
//     ray(cub);
// }

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
    // Rotate direction vector
    cub->game->dir_x = cub->game->dir_x * cos_angle - cub->game->dir_y * sin_angle;
    cub->game->dir_y = old_dir_x * sin_angle + cub->game->dir_y * cos_angle;
    
    // Rotate camera plane
    cub->game->plane_x = cub->game->plane_x * cos_angle - cub->game->plane_y * sin_angle;
    cub->game->plane_y = old_plane_x * sin_angle + cub->game->plane_y * cos_angle;
}

// int is_valid_position(t_cub *cub, float map_x, float map_y)
// {
//     // Check boundaries
//     if (map_x < 0 || map_x >= cub->game->map_width || 
//         map_y < 0 || map_y >= cub->game->map_height)
//         return 0;
    
//     // Check for walls
//     return (cub->game->map[(int)map_y][(int)map_x] != '1');
// }

int is_valid_position(t_cub *cub, float map_x, float map_y)
{
	char cell;

	cell = cub->game->map[(int)map_y][(int)map_x];
    if (map_x < 0 || map_x >= cub->game->map_width || 
        map_y < 0 || map_y >= cub->game->map_height)
        return 0;
    
    // Can't walk through walls
    if (cell == '1')
        return 0;
    
    // Can't walk through closed doors
    if (cell == 'D' && cub->game->door_state[(int)map_y][(int)map_x] == '1')
        return 0;
    
    return 1;
}

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
	// Example: rotate player depending on mouse movement

	if (last_x < 0)
		last_x = xpos;

	delta_x = xpos - last_x;

	if (delta_x != 0)
		rotate_player(cub, delta_x * 0.002f); // sensitivity factor
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
	// Update player position on minimap
	if (cub->textures->player && cub->textures->player->instances)
    {
        cub->textures->player->instances[0].x = (int)(cub->game->xp_pos * cub->game->minimap_scale);
        cub->textures->player->instances[0].y = (int)(cub->game->yp_pos * cub->game->minimap_scale);
    }
}