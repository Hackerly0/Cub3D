/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:52:48 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/17 18:52:14 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#define WIDTH 1200 
#define HEIGHT 600
#define TILE 64
#define P_SIZE 10

#include "../libft/libft.h"
#include <math.h>
#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_rays
{
    float distance;
    int hit_vertical;
    float x_new;
    float y_new;
    float m;
    float x_end;
    float y_end;
} t_rays;

typedef struct  s_colors
{
    int ceil[3];
    int floor[3];
    uint32_t ceil_col;
	uint32_t floor_col;
}   t_colors;

typedef struct s_dir
{
    char    *north_path;
    char    *south_path;
    char    *east_path;
    char    *west_path;
}   t_dir;

typedef struct s_textures
{
    mlx_image_t* pixel_ray;
    mlx_image_t* player;
    mlx_image_t* wall;
    mlx_texture_t *north;
    mlx_texture_t *south;
    mlx_texture_t *east;
    mlx_texture_t *west;
} t_textures;

typedef struct s_game
{
    mlx_t           *mlx;
    char            **map;
    float dir_x;
    float dir_y;
    char			facing_dir;//       N   //S   //W    //E
	double			xp_pos;    //          x + 0.5
	double			yp_pos;    //          y + 0.5
	int				map_height;//       4
	int				map_width; //        3
}   t_game;

typedef struct s_cub
{
    t_game *game;
    t_rays *rays;
    t_textures *textures;
    t_colors *colors;
    t_dir *dir;
} t_cub;


int	    ray(t_cub *cub);
float	calc_dist(t_cub *cub, float x, float y, float angle);
void	draw_ray(t_cub *cub, float angle, float *dist_array, int col);
void	cast_rays(t_cub *cub, float start, float step, float *dist);
void	draw_walls(t_cub *cub, float *dist, float fov);

void    rotate_player(t_cub *cub, float theta);
void    move_up_donw(t_cub *cub, char type);
void    move_left_rigth(t_cub *cub, char type);
void    my_keyhook(mlx_key_data_t keydata, void *structs);


// int     player_minimap(t_game *game, t_cub *cub);
// int	    ray_minimap(t_cub *cub);
// int    draw_minimap(t_cub *cub);
// void	draw_ray_minimap(t_cub *cub, float angle);

void    colores_set(t_cub *cub);
void    put_pixel(t_cub *cub, int i, int	begin, int end);
#endif