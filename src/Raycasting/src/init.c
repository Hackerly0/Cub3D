/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:53:22 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/18 16:35:38 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	facing_dir_n_s(t_cub *cub)
{
	if (cub->game->facing_dir == 'N')
	{
		cub->game->dir_x = 0;
		cub->game->dir_y = -1;
		cub->game->plane_x = 0.66f;
		cub->game->plane_y = 0;
	}
	else if (cub->game->facing_dir == 'S')
	{
		cub->game->dir_x = 0;
		cub->game->dir_y = 1;
		cub->game->plane_x = -0.66f;
		cub->game->plane_y = 0;
	}
}

void	facing_dir_e_w(t_cub *cub)
{
	if (cub->game->facing_dir == 'E')
	{
		cub->game->dir_x = 1;
		cub->game->dir_y = 0;
		cub->game->plane_x = 0;
		cub->game->plane_y = 0.66f;
	}
	else if (cub->game->facing_dir == 'W')
	{
		cub->game->dir_x = -1;
		cub->game->dir_y = 0;
		cub->game->plane_x = 0;
		cub->game->plane_y = -0.66f;
	}
}

void	init_struct_element2(t_cub *cub)
{
	if (cub->dir)
	{
		cub->dir->door_path = NULL;
		cub->dir->west_path = NULL;
		cub->dir->east_path = NULL;
		cub->dir->north_path = NULL;
		cub->dir->south_path = NULL;
	}
	if (cub->textures)
	{
		cub->textures->player = NULL;
		cub->textures->wall = NULL;
		cub->textures->pixel_ray = NULL;
		cub->textures->scery = NULL;
		cub->textures->north = NULL;
		cub->textures->south = NULL;
		cub->textures->east = NULL;
		cub->textures->west = NULL;
		cub->textures->door = NULL;
	}
}

void	init_struct_element(t_cub *cub)
{
	int	i;

	i = 0;
	if (cub->game)
	{
		cub->game->xp_pos = 0;
		cub->game->facing_dir = 'N';
		cub->game->yp_pos = 0;
		cub->game->showing_scery = 0;
		cub->game->scery_start_time = 0.0;
		cub->game->show_animated = 0;
		cub->game->num_doors = 0;
		cub->game->question_active = 0;
		cub->game->wrong_count = 0;
		cub->game->qa_img_count = 0;
		cub->game->ans = '\0';
		cub->game->current_qa = NULL;
		cub->game->mlx = NULL;
		cub->game->door_state = NULL;
		cub->game->map = NULL;
		while (i < QA_IMG_MAX)
			cub->game->qa_imgs[i++] = NULL;
	}
	init_struct_element2(cub);
}

int	init_image(t_cub *cub)
{
	int	minimap_width;
	int	minimap_height;

	minimap_height = 200;
	minimap_width = 200;
	cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
	if (!cub->textures->pixel_ray)
		return (1);
	cub->textures->wall = mlx_new_image(cub->game->mlx, minimap_width,
			minimap_height);
	if (!cub->textures->wall)
		return (1);
	cub->textures->player = mlx_new_image(cub->game->mlx, P_SIZE
			* MINIMAP_SCALE, P_SIZE * MINIMAP_SCALE);
	if (!cub->textures->player)
		return (1);
	return (0);
}
