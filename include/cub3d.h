/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:54:20 by hnisirat          #+#    #+#             */
/*   Updated: 2025/09/30 17:58:04 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#define WIDTH 1920
#define HEIGHT 1080
#define TILE 64
#define P_SIZE 20
#define MOVE_SPEED 0.1f
#define ROT_SPEED 0.05f
#define MINIMAP_SCALE 0.2f 

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <ctype.h>
# include <math.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_colors
{
	t_rgb		ceil;
	t_rgb		floor;
	uint32_t	ceil_col;
	uint32_t	floor_col;
}	t_colors;

typedef struct s_tex
{
	char	*path;
	void	*img;
	int		width;
	int		height;
}	t_tex;

typedef struct s_directions
{
	t_tex	north;
	t_tex	south;
	t_tex	east;
	t_tex	west;
}	t_directions;

typedef struct s_player
{
	double	x;
	double	y;
	char	dir;
}	t_player;

typedef struct s_vars
{
	char		**map;
	int			width;
	int			height;
	int			map_ended;
	t_player	player;
}	t_vars;

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
    // t_textures *textures;
    // t_colors *colors;
    t_dir *dir;
    // t_column	*col;
} t_cub;

typedef struct s_config
{
	t_colors		colors;
	t_directions	textures;
	t_vars			vars;
	t_cub			*cub;
}	t_config;


int		parse_cub(const char *path, t_config *cfg);
int		is_map_line(const char *s);
int		parse_tex_id(const char *s, char **out);
int		parse_rgb(const char *s, t_rgb *out);
int		parse_num(const char *s, int *i);
void	push_map_line(t_vars *v, const char *s);
int		pad_map_rect(t_vars *v);
int		ft_rowlen(const char *s);
void	ft_fill_spaces(char *dst, int start, int end);
int		ft_pad_one_row(char **row_ptr, int width);
void	free_config(t_config *cfg);
int		is_blank(const char *s);
int		starts_with_id(const char *s, const char *id);
int		handle_map_line(const char *line, t_config *cfg);
int		process_file_lines(int fd, t_config *cfg);
int		run_validations(t_config *cfg);
int		handle_north_south(const char *line, t_config *cfg);
int		handle_west_east(const char *line, t_config *cfg);
int		handle_colors(const char *line, t_config *cfg);
int		handle_header_line(const char *line, t_config *cfg, int *phase);
void	rstrip_newline(char *s);
int		is_ws(char c);
int		isnum(int c);
int		perr(const char *msg);
int		max(int a, int b);
void	ft_free(char **s, int j);
char	*strdup(const char *s);
size_t	strlen(const char *s);
int		validate_headers_complete(t_config *cfg);
int		validate_textures(t_config *cfg);
int		validate_colors(t_config *cfg);
int		validate_chars(t_vars *v);
int		validate_cub_file(const char *path);
int		validate_and_extract_player(t_vars *v);
int		validate_and_extract_player_enhanced(t_vars *v);
int		validate_map_walls(t_vars *v);
int		validate_map_with_floodfill(t_vars *v);
int		map_validation(t_vars *var);
int		is_allowed(char c);
int		is_spawn(char c);
int		is_walkable(char c);
int		is_valid_map_char(char c);
int		is_surrounded_by_walls(t_vars *v, int y, int x);
int		is_void_or_oob(t_vars *v, int y, int x);
int		flood_fill_recursive(char **map, int x, int y, t_vars *var);
char	**copy_map(char **map, int height);
int		warp_flood_fill(t_vars *var);

/* RAYCASTING */

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