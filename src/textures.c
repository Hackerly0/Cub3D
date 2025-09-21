// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   textures.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/09/17 15:02:47 by salshaha          #+#    #+#             */
// /*   Updated: 2025/09/20 13:16:50 by salshaha         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "cub.h"

uint32_t	get_pixel_color(mlx_texture_t *tex, int x, int y)
{
	int			i;
	uint8_t		*pixels;

	if (!tex || x < 0 || y < 0
		|| x >= (int)tex->width || y >= (int)tex->height)
		return (0xFF0000FF);
	pixels = tex->pixels;
	i = (y * tex->width + x) * 4;
	return ((pixels[i + 3] << 24) | (pixels[i] << 16)
		| (pixels[i + 1] << 8) | pixels[i + 2]);
}

mlx_texture_t	*get_wall_texture(t_cub *cub, int side, int step_x, int step_y)
{
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

void	get_texture_coords(t_cub *cub, mlx_texture_t *tex,
	float *wall_x, int *tex_x)
{
	if (cub->rays->side == 0)
		*wall_x = cub->game->yp_pos
			+ get_distance(cub) * cub->rays->ray_y;
	else
		*wall_x = cub->game->xp_pos
			+ get_distance(cub) * cub->rays->ray_x;
	*wall_x -= floor(*wall_x);
	*tex_x = (int)(*wall_x * tex->width);
	if ((cub->rays->side == 0 && cub->rays->step_x < 0)
		|| (cub->rays->side == 1 && cub->rays->step_y > 0))
		*tex_x = tex->width - *tex_x - 1;
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_x >= (int)tex->width)
		*tex_x = tex->width - 1;
}


// static uint32_t rgb_to_hex(int r, int g, int b)
// {
//     return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) |
//            ((b & 0xFF) << 8)  | 0xFF; // Alpha = 255
// }

// void    colores_set(t_cub *cub)
// {
// cub->colors->ceil[0] = 135; // R
// cub->colors->ceil[1] = 206; // G
// cub->colors->ceil[2] = 235; // B

// cub->colors->floor[0] = 34;
// cub->colors->floor[1] = 139;
// cub->colors->floor[2] = 34;
//     cub->colors->ceil_col = rgb_to_hex(cub->colors->ceil[0], cub->colors->ceil[1], cub->colors->ceil[2]);
// 	cub->colors->floor_col = rgb_to_hex(cub->colors->floor[0], cub->colors->floor[1], cub->colors->floor[2]);
// }

// uint32_t get_tex_pixel(mlx_texture_t *tex, int x, int y)
// {
//     if (!tex)
//         return 0xFFFFFFFF; // fallback white
//     if (x < 0) 
//         x = 0;
//     if (x >= (int)tex->width) 
//         x = tex->width - 1;
//     if (y < 0) 
//         y = 0;
//     if (y >= (int)tex->height) 
//         y = tex->height - 1;
//     uint32_t *pixels = (uint32_t *)tex->pixels;
//     return pixels[y * tex->width + x];
// }

// void put_wall_pixel(t_cub *cub, int i, int begin, int end, int tex_x, mlx_texture_t *texture)
// {
//     int y;
//     float tex_step;
//     float tex_pos;
//     int tex_y;

//     y = 0;
//     while (y < begin)
//         mlx_put_pixel(cub->textures->pixel_ray, i, y++, cub->colors->ceil_col);

//     // Draw wall with texture
//     tex_step = (float)texture->height / (end - begin);
//     tex_pos = 0.0f;
//     y = begin;
//     while (y < end)
//     {
//         tex_y = (int)tex_pos & (texture->height - 1);
//         mlx_put_pixel(cub->textures->pixel_ray, i, y, get_tex_pixel(texture, tex_x, tex_y));
//         tex_pos += tex_step;
//         y++;
//     }

//     y = end;
//     while (y < HEIGHT)
//         mlx_put_pixel(cub->textures->pixel_ray, i, y++, cub->colors->floor_col);
// }


// // void    put_pixel(t_cub *cub, int i, int begin, int end)
// // {
// //     int y;
// //     // mlx_texture_t *t;
// //     // int tex_y;
// //     // int tex_x;
// //     // uint32_t color;

// //     // if (wall_dir[0] == 'N') 
// //     //     t = cub->textures->walls->north;
// //     // else if (wall_dir[0] == 'S') 
// //     //     t = cub->textures->walls->south;
// //     // else if (wall_dir[0] == 'E') 
// //     //     t = cub->textures->walls->east;
// //     // else 
// //     //     t = cub->textures->walls->west;

// //     y = 0;
// //     while (y < begin)
// // 		mlx_put_pixel(cub->textures->pixel_ray, i, y++, cub->colors->ceil_col);
// // 	y = begin;
// // 	while (y < end)
// // 		mlx_put_pixel(cub->textures->pixel_ray, i, y++, 0xFF0000FF);
// // 	y = end;
// // 	while (y < HEIGHT)
// // 		mlx_put_pixel(cub->textures->pixel_ray, i, y++, cub->colors->floor_col);
// // }

// // void put_pixel(t_cub *cub, int i, int begin, int end)
// // {
// //     int y;
// //     mlx_texture_t *t;
// //     int tex_x;
// //     int tex_y;
// //     uint32_t color;

// //     if (cub->rays->hit_vertical)
// //     {
// //         if (cub->rays->x_end > cub->game->xp_pos)
// //             t = cub->textures->east;
// //         else
// //             t = cub->textures->west;
// //     }
// //     else
// //     {
// //         if (cub->rays->y_end > cub->game->yp_pos)
// //             t = cub->textures->south;
// //         else
// //             t = cub->textures->north;
// //     }
// //     y = 0;
// //     while (y < begin)
// //         mlx_put_pixel(cub->textures->pixel_ray, i, y++, cub->colors->ceil_col);
// //     y = begin;
// //     while (y < end)
// //     {
// //         tex_y = (y - begin) * t->height / (end - begin);
// //         tex_x = i * t->width / WIDTH;
// //         color = t->pixels[tex_y * t->width + tex_x];
// //         mlx_put_pixel(cub->textures->pixel_ray, i, y, color);
// //         y++;
// //     }
// //     y = end;
// //     while (y < HEIGHT)
// //         mlx_put_pixel(cub->textures->pixel_ray, i, y++, cub->colors->floor_col);
// // }
