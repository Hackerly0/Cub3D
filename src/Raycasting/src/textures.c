/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:02:47 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/13 22:52:18 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8)
		| ((b & 0xFF)));
}

void	set_colors(t_cub *cub)
{
	cub->colors->ceil_col = rgb_to_hex(cub->colors->ceil[0],
			cub->colors->ceil[1], cub->colors->ceil[2]);
	cub->colors->floor_col = rgb_to_hex(cub->colors->floor[0],
			cub->colors->floor[1], cub->colors->floor[2]);
}

uint32_t	get_pixel_color(mlx_texture_t *tex, int x, int y)
{
	int		i;
	uint8_t	*pixels;

	if (!tex || x < 0 || y < 0 || x >= (int)tex->width || y >= (int)tex->height)
		return (0xFF0000FF);
	pixels = tex->pixels;
	i = (y * tex->width + x) * 4;
	return ((pixels[i] << 24) | (pixels[i + 1] << 16)
		| (pixels[i + 2] << 8) | 0xFF);
}

mlx_texture_t	*get_wall_texture(t_cub *cub, int side, int step_x, int step_y)
{
	if (cub->rays->hit_cell == 'D')
	{
			return (show_animated(cub));
	}
	if (side == 0)
	{
		if (step_x > 0)
			return (cub->textures->east);
		return (cub->textures->west);
	}
	if (step_y > 0)
		return (cub->textures->south);
	return (cub->textures->north);
}

void	get_texture_coords(t_cub *cub, mlx_texture_t *tex, float *wall_x,
		int *tex_x)
{
	if (!tex)
		return ;
	if (cub->rays->side == 0)
		*wall_x = cub->game->yp_pos + get_distance(cub) * cub->rays->ray_y;
	else
		*wall_x = cub->game->xp_pos + get_distance(cub) * cub->rays->ray_x;
	*wall_x -= floor(*wall_x);
	*tex_x = (int)(*wall_x * tex->width);
	if ((cub->rays->side == 0 && cub->rays->step_x < 0) || (cub->rays->side == 1
			&& cub->rays->step_y > 0))
		*tex_x = tex->width - *tex_x - 1;
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_x >= (int)tex->width)
		*tex_x = tex->width - 1;
}
