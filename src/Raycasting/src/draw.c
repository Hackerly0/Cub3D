/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:23:50 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/08 17:01:37 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_distance(t_cub *cub)
{
	float	dist;

	if (cub->rays->side == 0)
	{
		dist = (cub->rays->map_x - cub->game->xp_pos + (1 - cub->rays->step_x)
				/ 2.0f) / cub->rays->ray_x;
	}
	else
	{
		dist = (cub->rays->map_y - cub->game->yp_pos + (1 - cub->rays->step_y)
				/ 2.0f) / cub->rays->ray_y;
	}
	if (dist < 0.001f)
		dist = 0.001f;
	return (dist);
}

void	draw_ceiling_floor(t_cub *cub, t_column col)
{
	int	y;

	y = 0;
	while (y < col.start)
	{
		mlx_put_pixel(cub->textures->pixel_ray,
			col.x, y, cub->colors->ceil_col);
		y++;
	}
	y = col.end;
	while (y < HEIGHT)
	{
		mlx_put_pixel(cub->textures->pixel_ray,
			col.x, y, cub->colors->floor_col);
		y++;
	}
}

void	draw_wall_texture(t_cub *cub, mlx_texture_t *tex, t_column *col)
{
	float		tex_step;
	float		tex_pos;
	int			y;
	int			tex_y;
	uint32_t	color;

	if (!tex)
		return ;
	get_texture_coords(cub, tex, &col->wall_x, &col->tex_x);
	tex_step = (float)tex->height / col->wall_height;
	tex_pos = (col->start - HEIGHT / 2 + col->wall_height / 2) * tex_step;
	y = col->start;
	while (y < col->end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)tex->height)
			tex_y = tex->height - 1;
		color = get_pixel_color(tex, col->tex_x, tex_y);
		if (cub->rays->side == 1)
			color = ((color >> 1) & 0x7F7F7F00) | 0xFF;
		mlx_put_pixel(cub->textures->pixel_ray, col->x, y++, color);
		tex_pos += tex_step;
	}
}

void	draw_wall(t_cub *cub, t_column col)
{
	mlx_texture_t	*tex;

	tex = get_wall_texture(cub, cub->rays->side, cub->rays->step_x,
			cub->rays->step_y);
	draw_ceiling_floor(cub, col);
	draw_wall_texture(cub, tex, &col);
}

void	draw_column(t_cub *cub, int x, float dist)
{
	t_column	col;

	col.x = x;
	col.wall_height = (int)(HEIGHT / dist);
	col.start = (-col.wall_height / 2) + (HEIGHT / 2);
	col.end = (col.wall_height / 2) + (HEIGHT / 2);
	if (col.start < 0)
		col.start = 0;
	if (col.end >= HEIGHT)
		col.end = HEIGHT - 1;
	draw_wall(cub, col);
}
