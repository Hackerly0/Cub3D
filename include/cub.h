/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:52:48 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/29 16:10:54 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

// #define WIDTH 1200 
// #define HEIGHT 600
#define WIDTH 1920
#define HEIGHT 1080
#define TILE 64
#define P_SIZE 20
#define MOVE_SPEED 0.1f
#define ROT_SPEED 0.05f
#define MINIMAP_SCALE 0.2f 


#include "../libft/libft.h"
#include <math.h>
#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_rays
{
    float   ray_x;      // ray direction X
    float   ray_y;      // ray direction Y

    float   delta_x;    // length of ray from one x-side to next
    float   delta_y;    // length of ray from one y-side to next

    int     map_x;      // current square X in the map
    int     map_y;      // current square Y in the map

    int     step_x;     // +1 or -1 step direction in X
    int     step_y;     // +1 or -1 step direction in Y

    float   side_x;     // distance from start to next x-side
    float   side_y;     // distance from start to next y-side

    int     side;       // 0 if vertical wall, 1 if horizontal
    float   distance;   // perpendicular distance to wall

    int     tex_x;      // X coordinate in texture
    float   wall_x;     // wall hit position (for texture)
    float   tex_step;   // step for texture mapping
    float   tex_pos;    // current texture position
    char    hit_cell;  // Cell type that was hit (e.g., '1' for wall, 'D' for door)
}   t_rays;

typedef struct s_column
{
	int			x;
	int			wall_height;
	int			start;
	int			end;
	float		wall_x;
	int			tex_x;
	int			tex_y;
}	t_column;

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
    char    *door_path;
}   t_dir;

typedef struct s_textures
{
    mlx_image_t* pixel_ray;
    mlx_image_t* player;
    mlx_image_t* wall;
    mlx_image_t* space;
    mlx_texture_t *north;
    mlx_texture_t *south;
    mlx_texture_t *east;
    mlx_texture_t *west;
    mlx_texture_t *door;
} t_textures;

typedef struct s_game
{
    mlx_t           *mlx;
    char            **map;
    float dir_x;
    float dir_y;
        float plane_x;  // Add these camera plane variables
    float plane_y;  // Add these camera plane variables
    char			facing_dir;//       N   //S   //W    //E
	double			xp_pos;    //          x + 0.5
	double			yp_pos;    //          y + 0.5
	int				map_height;//       4
	int				map_width; //        3
    float minimap_scale;

    char    **door_state;;
}   t_game;

typedef struct s_cub
{
    t_game *game;
    t_rays *rays;
    t_textures *textures;
    t_colors *colors;
    t_dir *dir;
    // t_column	*col;
} t_cub;


// int	    ray(t_cub *cub);
// float	calc_dist(t_cub *cub, float x, float y, float angle);
// void draw_walls(t_cub *cub, float *dist, float fov, float *ray_hit_x, float *ray_hit_y);
// void    rotate_player(t_cub *cub, float theta);
// void    move_up_donw(t_cub *cub, char type);
// void	move_left_right(t_cub *cub, char type);
// void    my_keyhook(mlx_key_data_t keydata, void *structs);

// void put_wall_pixel(t_cub *cub, int i, int begin, int end, int tex_x, mlx_texture_t *texture);
// // int     player_minimap(t_game *game, t_cub *cub);
// // int	    ray_minimap(t_cub *cub);
// // int    draw_minimap(t_cub *cub);
// // void	draw_ray_minimap(t_cub *cub, float angle);

// void    colores_set(t_cub *cub);
// void    put_pixel(t_cub *cub, int i, int	begin, int end);







// Add these function prototypes to your cub.h file

// Raycasting functions
int     ray(t_cub *cub);
void    colores_set(t_cub *cub);
void    put_wall_pixel(t_cub *cub, int i, int begin, int end, int tex_x, mlx_texture_t *texture);

// Movement and input functions  
void    my_keyhook(mlx_key_data_t keydata, void *structs);
void keyhook(void *param);
void    rotate_player(t_cub *cub, float theta);
void    move_up_donw(t_cub *cub, char type);
void    move_left_right(t_cub *cub, char type);
void	cursor(double xpos, double ypos, void *param);

// Initialization functions
void    facing_dir(t_cub *cub);
int     struct_init(t_cub *cub);
int     ft_free_struct(t_cub *cub, int type);

// Map functions
void    init_map_from_sample(t_game *g, t_cub *cub);

void move_player(t_cub *cub, float move_x, float move_y);
void handle_movement_keys(t_cub *cub);
void move_player(t_cub *cub, float move_x, float move_y);
uint32_t	get_pixel_color(mlx_texture_t *tex, int x, int y);
mlx_texture_t	*get_wall_texture(t_cub *cub, int side, int step_x, int step_y);
void	get_texture_coords(t_cub *cub, mlx_texture_t *tex, float *wall_x, int *tex_x);
float	get_distance(t_cub *cub);
void	cast_ray(t_cub *cub, int x);
int	ray(t_cub *cub);
void	draw_column(t_cub *cub, int x, float dist);

int	init_image(t_cub *cub);
//minimap
int    draw_minimap(t_cub *cub);
int    player_minimap(t_cub *cub);
void chosse_scale(t_cub *cub);


void init_door_states(t_game *game);
#endif