/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animated_door.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:00:22 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/14 18:18:58 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_if_texture_fail(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->textures->frame_door[i])
	{
		if (!cub->textures->frame_door[i])
		{
			printf("Error: Failed to load collectible textures\n");
			ft_free_struct(cub, 1);
			exit(1);
		}
		i++;
	}
	cub->textures->current_door_frame = 0;
}

void	exit_load(char *path, char *number, char *printed_path, t_cub *cub)
{
	if (path)
		free(path);
	if (number)
		free(number);
	if (printed_path)
		free(printed_path);
	if (cub)
		ft_free_struct(cub, 1);
	exit(1);
}

int	load_frame_textures(t_cub *cub)
{
	int		i;
	char	*path;
	char	*number;
	char	*printed_path;

	i = 0;
	while (i < 21)
	{
		number = ft_itoa(i + 1);
		if (!number)
			exit_load(NULL, NULL, NULL, cub);
		path = ft_strjoin("./textures/open/open_", number);
		if (!path)
			exit_load(NULL, number, NULL, cub);
		printed_path = ft_strjoin(path, ".png");
		if (!printed_path)
			exit_load(path, number, NULL, cub);
		cub->textures->frame_door[i++] = mlx_load_png(printed_path);
		free(printed_path);
		free(path);
		free(number);
	}
	cub->textures->frame_door[21] = NULL;
	check_if_texture_fail(cub);
	return (0);
}

mlx_texture_t	*show_animated(t_cub *cub)
{
	static double	last_frame_time = 0;
	double			current_time;
	double			frame_delay;

	// last_frame_time = 0;
	frame_delay = 0.1;
	if (cub->game->show_animated)
	{
		current_time = mlx_get_time();
		if (current_time - last_frame_time >= frame_delay)
		{
			cub->textures->current_door_frame++;
			if (cub->textures->current_door_frame > 20)
			{
				print_statment_win();
				ft_free_struct(cub, 0);
				exit(0);
				return NULL;
			}
			last_frame_time = current_time;
		}
		return (cub->textures->frame_door[cub->textures->current_door_frame]);
	}
	return (cub->textures->door);
}
