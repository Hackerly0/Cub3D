/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:00:00 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/10 22:38:44 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void number_of_door(t_game *game)
{
	int y;
	int x;
	int count;

	y = 0;
	count = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	game->num_doors = count;
}

void	init_door_states(t_game *game)
{
	int	y;
	int	x;

	game->door_state = malloc(game->map_height * sizeof(char *));
	if (!game->door_state)
		return ;
	y = 0;
	while (y < game->map_height)
	{
		game->door_state[y] = malloc(game->map_width + 1);
		if (!game->door_state[y])
			return ;
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
	number_of_door(game);
}

int	is_valid_position(t_cub *cub, float map_x, float map_y)
{
	char	cell;

	cell = cub->game->map[(int)map_y][(int)map_x];
	if (map_x < 0 || map_x >= cub->game->map_width
		|| map_y < 0 || map_y >= cub->game->map_height)
		return (0);
	if (cell == '1')
		return (0);
	if (cell == 'D' && cub->game->door_state[(int)map_y][(int)map_x] == '1')
		return (0);
	return (1);
}
int load_collectible_textures(t_cub *cub);

// void load_ceil_frames(t_cub *cub)
// {
// 	cub->textures->ceiling[0] = mlx_load_png("./textures/skyy_1.png");
// 	cub->textures->ceiling[1] = mlx_load_png("./textures/skyy_2.png");
// 	cub->textures->ceiling[2] = mlx_load_png("./textures/skyy_3.png");
// 	cub->textures->ceiling[3] = mlx_load_png("./textures/skyy_4.png");
// 	if (!cub->textures->ceiling[0]
// 		|| !cub->textures->ceiling[1]
// 		|| !cub->textures->ceiling[2]
// 		|| !cub->textures->ceiling[3])
// 	{
// 		printf("Error: Failed to load ceiling textures\n");
// 		return ;
// 	}
// }

int	load_textures(t_cub *cub)
{
	
	cub->textures->north = mlx_load_png(cub->dir->north_path);
	cub->textures->south = mlx_load_png(cub->dir->south_path);
	cub->textures->east = mlx_load_png(cub->dir->east_path);
	cub->textures->west = mlx_load_png(cub->dir->west_path);
	cub->textures->door = mlx_load_png("./textures/door.png");
	cub->textures->scery = mlx_load_png("./textures/scery.png");
	if (!cub->textures->north || !cub->textures->south
		|| !cub->textures->east || !cub->textures->west
		|| !cub->textures->door || !cub->textures->scery)
	{
		printf("Error: Failed to load one or more textures\n");
		return (1);
	}
	if (load_collectible_textures(cub))
        return (1);
	// load_ceil_frames(cub);
	return (0);
}

int	raycasting(t_cub *cub)
{
	cub->game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!cub->game->mlx)
		return (ft_free_struct(cub, 1));
	if (load_textures(cub))
		return (ft_free_struct(cub, 1));
	if (init_image(cub))
		return (ft_free_struct(cub, 1));
	chosse_scale(cub);
	draw_minimap(cub);
	player_minimap(cub);
	mlx_image_to_window(cub->game->mlx, cub->textures->pixel_ray, 0, 0);
	mlx_image_to_window(cub->game->mlx, cub->textures->wall, 0, 0);
	mlx_image_to_window(cub->game->mlx, cub->textures->player,
		(int)(cub->game->xp_pos * cub->game->minimap_scale) - (P_SIZE
			* cub->game->minimap_scale) / 2, (int)(cub->game->yp_pos
			* cub->game->minimap_scale) - (P_SIZE
			* cub->game->minimap_scale) / 2);
	mlx_loop_hook(cub->game->mlx, keyhook, cub);
	mlx_key_hook(cub->game->mlx, space_hook, cub);
	mlx_cursor_hook(cub->game->mlx, cursor, cub);
	if (ray(cub))
		return (ft_free_struct(cub, 1));
	mlx_loop(cub->game->mlx);
	return (ft_free_struct(cub, 0));
}
