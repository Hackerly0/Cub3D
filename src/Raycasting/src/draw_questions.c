/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_questions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:25:21 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/17 23:38:39 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_text_imgs(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->game->qa_img_count)
	{
		if (cub->game->qa_imgs[i])
			mlx_delete_image(cub->game->mlx, cub->game->qa_imgs[i]);
		cub->game->qa_imgs[i] = NULL;
		i++;
	}
	cub->game->qa_img_count = 0;
}

void	draw_overlay(t_cub *cub)
{
	int	x;
	int	y;
	int	bounds[4];

	bounds[0] = WIDTH / 4;
	bounds[1] = HEIGHT / 3;
	bounds[2] = WIDTH - bounds[0];
	bounds[3] = HEIGHT - bounds[1];
	if (!cub->textures->pixel_ray || !cub->textures->pixel_ray->enabled)
		return ;
	if (cub->textures->pixel_ray->width != WIDTH
		|| cub->textures->pixel_ray->height != HEIGHT)
		return ;
	y = bounds[1];
	while (y < bounds[3])
	{
		x = bounds[0];
		while (x < bounds[2])
			mlx_put_pixel(cub->textures->pixel_ray, x++, y, 0xFFFFFF80);
		y++;
	}
}

void	draw_text_line(t_cub *cub, char *line, int x, int y)
{
	mlx_image_t	*img;

	img = mlx_put_string(cub->game->mlx, line, x, y);
	if (img && cub->game->qa_img_count < QA_IMG_MAX)
		cub->game->qa_imgs[cub->game->qa_img_count++] = img;
}
