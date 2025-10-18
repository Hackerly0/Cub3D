/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparing_question.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:03:11 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/18 11:17:07 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*strip_star(const char *s)
{
	size_t	len;
	char	*out;
	size_t	r;
	size_t	w;

	len = ft_strlen(s);
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	r = 0;
	w = 0;
	while (r < len)
	{
		if (s[r] != '*')
			out[w++] = s[r];
		r++;
	}
	out[w] = '\0';
	return (out);
}

void	process_qa_line(t_cub *cub, char **qa, int i, int y)
{
	char	*line;
	int		text_width;
	int		x;

	if (i >= 1 && i <= 4)
		line = strip_star(qa[i]);
	else
		line = ft_strdup(qa[i]);
	if (!line)
		return ;
	text_width = ft_strlen(line) * 10;
	x = (WIDTH / 2) - (text_width / 2);
	draw_text_line(cub, line, x, y + (i * 30));
	free(line);
}

void	draw_centered_text(t_cub *cub, char **qa)
{
	int	i;
	int	y;
	int	total_lines;

	clear_text_imgs(cub);
	draw_overlay(cub);
	total_lines = 0;
	while (qa[total_lines])
		total_lines++;
	y = (HEIGHT / 2) - ((total_lines * 30) / 2);
	i = 0;
	while (qa[i])
	{
		process_qa_line(cub, qa, i, y);
		i++;
	}
}

void	clear_question_display(t_cub *cub)
{
	clear_text_imgs(cub);
	if (cub->textures->pixel_ray && cub->textures->pixel_ray->enabled)
	{
		mlx_delete_image(cub->game->mlx, cub->textures->pixel_ray);
		cub->textures->pixel_ray = mlx_new_image(cub->game->mlx,
				WIDTH, HEIGHT);
		if (cub->textures->pixel_ray)
		{
			mlx_image_to_window(cub->game->mlx,
				cub->textures->pixel_ray, 0, 0);
			if (cub->textures->pixel_ray->instances)
				cub->textures->pixel_ray->instances[0].z = 0;
			if (cub->textures->wall && cub->textures->wall->instances)
				cub->textures->wall->instances[0].z = 1;
			if (cub->textures->player && cub->textures->player->instances)
				cub->textures->player->instances[0].z = 2;
		}
	}
}

void	load_new_question(t_cub *cub)
{
	ft_free(cub->game->current_qa, -1);
	cub->game->current_qa = grab_questions();
	if (!cub->game->current_qa)
	{
		printf("Error: Failed to load question\n");
		return ;
	}
	draw_centered_text(cub, cub->game->current_qa);
}
