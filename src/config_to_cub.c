/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_to_cub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:59:15 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/14 21:47:53 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	transfer_colors(t_config *cfg, t_cub *cub)
{
	cub->colors->ceil[0] = cfg->colors.ceil.r;
	cub->colors->ceil[1] = cfg->colors.ceil.g;
	cub->colors->ceil[2] = cfg->colors.ceil.b;
	cub->colors->floor[0] = cfg->colors.floor.r;
	cub->colors->floor[1] = cfg->colors.floor.g;
	cub->colors->floor[2] = cfg->colors.floor.b;
	cub->colors->ceil_col = rgb_to_uint32(cfg->colors.ceil);
	cub->colors->floor_col = rgb_to_uint32(cfg->colors.floor);
	return (0);
}

static int	transfer_texture_paths(t_config *cfg, t_cub *cub)
{
	cub->dir->north_path = ft_strdup(cfg->textures.north.path);
	if (!cub->dir->north_path)
		return (-1);
	cub->dir->south_path = ft_strdup(cfg->textures.south.path);
	if (!cub->dir->south_path)
		return (-1);
	cub->dir->east_path = ft_strdup(cfg->textures.east.path);
	if (!cub->dir->east_path)
		return (-1);
	cub->dir->west_path = ft_strdup(cfg->textures.west.path);
	if (!cub->dir->west_path)
		return (-1);
	cub->dir->door_path = NULL;
	return (0);
}

static int	transfer_map(t_config *cfg, t_cub *cub)
{
	int	i;

	cub->game->map_height = cfg->vars.height;
	cub->game->map_width = cfg->vars.width;
	cub->game->map = (char **)malloc(sizeof(char *)
			* (cfg->vars.height + 1));
	if (!cub->game->map)
		return (-1);
	i = 0;
	while (i < cfg->vars.height)
	{
		cub->game->map[i] = ft_strdup(cfg->vars.map[i]);
		if (!cub->game->map[i])
		{
			while (--i >= 0)
				free(cub->game->map[i]);
			free(cub->game->map);
			return (-1);
		}
		i++;
	}
	cub->game->map[i] = NULL;
	return (0);
}

static int	transfer_player(t_config *cfg, t_cub *cub)
{
	cub->game->xp_pos = cfg->vars.player.x + 0.5;
	cub->game->yp_pos = cfg->vars.player.y + 0.5;
	cub->game->facing_dir = cfg->vars.player.dir;
	return (0);
}

int	config_to_cub(t_config *cfg, t_cub *cub)
{
	if (!cfg || !cub)
		return (-1);
	if (transfer_colors(cfg, cub) == -1)
		return (-1);
	if (transfer_texture_paths(cfg, cub) == -1)
		return (-1);
	if (transfer_map(cfg, cub) == -1)
		return (-1);
	if (transfer_player(cfg, cub) == -1)
		return (-1);
	init_door_states(cub->game);
	return (0);
}
