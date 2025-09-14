/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:52:48 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/14 20:31:37 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#define WIDTH 1200 
#define HEIGHT 600  

#include "../libft/libft.h"
#include <math.h>
#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_rays
{
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
}   t_colors;

typedef struct s_dir
{
    char    *north;
    char    *south;
    char    *east;
    char    *west;
}   t_dir;

typedef struct s_textures
{
    mlx_image_t* pixel_ray;
    mlx_image_t* player;
    mlx_image_t* wall;
} t_textures;

typedef struct s_game
{
    mlx_t           *mlx;
    char            **map;
    float dir_x;
    float dir_y;
    // float             player_angle_x;
    // float             player_angle_y;
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
} t_cub;

#endif