/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:25:52 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/17 23:28:50 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	start_question_for_door(int check_x, int check_y, t_cub *cub)
{
	if (cub->game->door_state[check_y][check_x] == '1')
	{
		cub->game->door_check_x = check_x;
		cub->game->door_check_y = check_y;
		clear_text_imgs(cub);
		load_new_question(cub);
		cub->game->question_active = 1;
		cub->game->wrong_count = 0;
		cub->game->ans = '\0';
	}
}

void	toggle_nearest_door(t_cub *cub)
{
	int		check_x;
	int		check_y;
	float	check_dist;

	check_dist = 1.5f;
	check_x = (int)(cub->game->xp_pos + cub->game->dir_x * check_dist);
	check_y = (int)(cub->game->yp_pos + cub->game->dir_y * check_dist);
	if (check_x >= 0 && check_x < cub->game->map_width
		&& check_y >= 0 && check_y < cub->game->map_height)
	{
		if (cub->game->map[check_y][check_x] == 'D')
			start_question_for_door(check_x, check_y, cub);
	}
}

void	handle_question_key(t_cub *cub, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_1)
		cub->game->ans = '1';
	else if (keydata.key == MLX_KEY_2)
		cub->game->ans = '2';
	else if (keydata.key == MLX_KEY_3)
		cub->game->ans = '3';
	else if (keydata.key == MLX_KEY_4)
		cub->game->ans = '4';
	else
		return ;
	process_answer(cub);
}

void	combined_key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (cub->game->question_active)
		handle_question_key(cub, keydata);
	else if (keydata.key == MLX_KEY_SPACE)
		toggle_nearest_door(cub);
}
