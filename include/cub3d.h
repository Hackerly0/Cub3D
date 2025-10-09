
#ifndef CUB3D_H
# define CUB3D_H

/* ========================================================================== */
/*                                  INCLUDES                                  */
/* ========================================================================== */

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <ctype.h>
# include <math.h>

/* ========================================================================== */
/*                                   DEFINES                                  */
/* ========================================================================== */

/* Function Prototypes */
// void	draw_center_square(t_cub *cub);

# define WIDTH 1280
# define HEIGHT 720
# define TILE 64
# define P_SIZE 20
# define MOVE_SPEED 0.1f
# define ROT_SPEED 0.05f
# define MINIMAP_SCALE 0.2f

/* ========================================================================== */
/*                              PARSING STRUCTURES                            */
/* ========================================================================== */

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

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

typedef struct s_parse_colors
{
	t_rgb	ceil;
	t_rgb	floor;
}	t_parse_colors;

typedef struct s_vars
{
	char		**map;
	int			width;
	int			height;
	int			map_ended;
	t_player	player;
}	t_vars;

typedef struct s_config
{
	t_parse_colors	colors;
	t_directions	textures;
	t_vars			vars;
}	t_config;

/* ========================================================================== */
/*                            RAYCASTING STRUCTURES                           */
/* ========================================================================== */

typedef struct s_rays
{
	float	ray_x;
	float	ray_y;
	float	delta_x;
	float	delta_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	float	side_x;
	float	side_y;
	int		side;
	float	distance;
	int		tex_x;
	float	wall_x;
	float	tex_step;
	float	tex_pos;
	char	hit_cell;
}	t_rays;

typedef struct s_column
{
	int		x;
	int		wall_height;
	int		start;
	int		end;
	float	wall_x;
	int		tex_x;
	int		tex_y;
}	t_column;

typedef struct s_colors
{
	int			ceil[3];
	int			floor[3];
	uint32_t	ceil_col;
	uint32_t	floor_col;
}	t_colors;

typedef struct s_dir
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
	char	*door_path;
}	t_dir;

typedef struct s_textures
{
	mlx_image_t		*pixel_ray;
	mlx_image_t		*player;
	mlx_image_t		*wall;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*door;
	mlx_texture_t	*scery;
}	t_textures;

typedef struct s_game
{
	mlx_t	*mlx;
	char	**map;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	char	facing_dir;
	double	xp_pos;
	double	yp_pos;
	int		map_height;
	int		map_width;
	float	minimap_scale;
	char	**door_state;
	int		showing_scery;        // ADD THIS
	double	scery_start_time;     // ADD THIS

}	t_game;

typedef struct s_cub
{
	t_game		*game;
	t_rays		*rays;
	t_textures	*textures;
	t_colors	*colors;
	t_dir		*dir;
}	t_cub;

/* ========================================================================== */
/*                           PARSING FUNCTIONS                                */
/* ========================================================================== */

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
uint32_t	rgb_to_hex(int r, int g, int b);
void		facing_dir_n_s(t_cub *cub);
void		facing_dir_e_w(t_cub *cub);
void		drain_gnl(int fd);

/* ========================================================================== */
/*                          VALIDATION FUNCTIONS                              */
/* ========================================================================== */

int     raycasting(t_cub *cub);
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
int		validate_door_accessibility(t_vars *v);

/* ========================================================================== */
/*                           RAYCASTING FUNCTIONS                             */
/* ========================================================================== */

int				ray(t_cub *cub);
void			colores_set(t_cub *cub);
void			put_wall_pixel(t_cub *cub, int i, int begin, int end,
					int tex_x, mlx_texture_t *texture);
void			cast_ray(t_cub *cub, int x);
void			draw_column(t_cub *cub, int x, float dist);
float			get_distance(t_cub *cub);
uint32_t		get_pixel_color(mlx_texture_t *tex, int x, int y);
mlx_texture_t	*get_wall_texture(t_cub *cub, int side, int step_x, int step_y);
void			get_texture_coords(t_cub *cub, mlx_texture_t *tex,
					float *wall_x, int *tex_x);

/* ========================================================================== */
/*                          MOVEMENT & INPUT FUNCTIONS                        */
/* ========================================================================== */

void	keyhook(void *param);
void	rotate_player(t_cub *cub, float theta);
void	cursor(double xpos, double ypos, void *param);
void	move_player(t_cub *cub, float move_x, float move_y);
void	handle_movement_keys(t_cub *cub);
void 	toggle_nearest_door(t_cub *cub);
int 	is_valid_position(t_cub *cub, float map_x, float map_y);

/* ========================================================================== */
/*                        INITIALIZATION FUNCTIONS                            */
/* ========================================================================== */

void	facing_dir(t_cub *cub);
int		struct_init(t_cub *cub);
int		ft_free_struct(t_cub *cub, int type);
void	init_map_from_sample(t_game *g, t_cub *cub);
int		init_image(t_cub *cub);
void	init_door_states(t_game *game);

/* ========================================================================== */
/*                            MINIMAP FUNCTIONS                               */
/* ========================================================================== */

int		draw_minimap(t_cub *cub);
int		player_minimap(t_cub *cub);
void	chosse_scale(t_cub *cub);

/* ========================================================================== */
/*                            TRANSFER FUNCTION                               */
/* ========================================================================== */

int		config_to_cub(t_config *cfg, t_cub *cub);

/* ========================================================================== */
/*                            UTILITY FUNCTIONS                               */
/* ========================================================================== */

int		is_ws(char c);
int		isnum(int c);
int		perr(const char *msg);
int		max(int a, int b);
void	ft_free(char **s, int j);
char	*strdup(const char *s);
size_t	strlen(const char *s);



void space_hook(mlx_key_data_t keydata, void* param);
void print_qa(char **qa);
char	**grab_questions(void);

#endif