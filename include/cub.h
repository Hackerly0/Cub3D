/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:52:48 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/09 17:03:38 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#define WIDTH 1200 
#define HEIGHT 600  

#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_dim
{
    
} t_dim;

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

typedef struct s_game
{
    mlx_t *mlx;
    char    **map;
    char			facing_dir;//       N   //S   //W    //E
	double			xp_pos; //          x + 0.5
	double			yp_pos; //          y + 0.5
	int				map_height;//       4
	int				map_width;//        3
}   t_game;



#endif