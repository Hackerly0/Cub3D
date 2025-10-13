/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:56:49 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/13 22:42:46 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	free_collect_frames(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->textures->frame_door[i])
	{
		if (cub->textures->frame_door[i])
			mlx_delete_texture(cub->textures->frame_door[i]);
		i++;
	}
}
	
void	free_textures(t_cub *cub)
{
	if (cub && cub->textures && cub->game && cub->game->mlx)
	{
		if (cub->textures->pixel_ray)
			mlx_delete_image(cub->game->mlx, cub->textures->pixel_ray);
		if (cub->textures->player)
			mlx_delete_image(cub->game->mlx, cub->textures->player);
		if (cub->textures->wall)
			mlx_delete_image(cub->game->mlx, cub->textures->wall);
		if (cub->textures->scery)
			mlx_delete_texture(cub->textures->scery);
		if (cub->textures->north)
			mlx_delete_texture(cub->textures->north);
		if (cub->textures->south)
			mlx_delete_texture(cub->textures->south);
		if (cub->textures->east)
			mlx_delete_texture(cub->textures->east);
		if (cub->textures->west)
			mlx_delete_texture(cub->textures->west);
		if (cub->textures->door)
			mlx_delete_texture(cub->textures->door);
		free_collect_frames(cub);
	}
}

void	free_td_array(t_game *game, char **string, int limit)
{
	int	i;

	if (game && string)
	{
		i = 0;
		while (i < limit)
		{
			if (string[i])
				free(string[i]);
			i++;
		}
		free(string);
		string = NULL;
	}
}

void	ft_free_dir(t_dir *dir)
{
	if (dir)
	{
		if (dir->north_path)
			free(dir->north_path);
		if (dir->south_path)
			free(dir->south_path);
		if (dir->east_path)
			free(dir->east_path);
		if (dir->west_path)
			free(dir->west_path);
		if (dir->door_path)
			free(dir->door_path);
		free(dir);
	}
}

int	ft_free_struct(t_cub *cub, int type)
{
	if (!cub)
		return (type);
	free_textures(cub);
	free_td_array(cub->game, cub->game->door_state, cub->game->map_height);
	free_td_array(cub->game, cub->game->map, cub->game->map_height);
	ft_free_dir(cub->dir);
	if (cub->game && cub->game->mlx)
		mlx_terminate(cub->game->mlx);
	if (cub->game)
		free(cub->game);
	if (cub->rays)
		free(cub->rays);
	if (cub->textures)
		free(cub->textures);
	if (cub->colors)
		free(cub->colors);
	free(cub);
	return (type);
}
