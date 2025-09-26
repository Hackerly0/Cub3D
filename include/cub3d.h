#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>

/* ================= Colors ================= */
typedef struct s_rgb
{
	int r;
	int g;
	int b;
}   t_rgb;

typedef struct s_colors
{
	t_rgb ceil;
	t_rgb floor;
}   t_colors;

/* ================= Textures ================= */
typedef struct s_tex
{
	char *path;     // file path from parser
	void *img;      // mlx_xpm_file_to_image pointer (loaded later)
	int   width;
	int   height;
}   t_tex;

typedef struct s_directions
{
	t_tex north;
	t_tex south;
	t_tex east;
	t_tex west;
}   t_directions;

/* ================= Map & Player ================= */
typedef struct s_player
{
	double x;       // spawn position X
	double y;       // spawn position Y
	char   dir;     // 'N', 'S', 'E', 'W'
}   t_player;

typedef struct s_vars
{
	char     **map;   // 2D array of map (padded)
	int       width;  // max map width
	int       height; // number of map rows
	t_player  player;
}   t_vars;

/* ================= Master Config ================= */
typedef struct s_config
{
	t_colors     colors;
	t_directions textures;
	t_vars       vars;
}   t_config;

/* ================= Main Parser ================= */
int		parse_cub(const char *path, t_config *cfg);

/* ================= Parser Helpers ================= */
int		is_map_line(const char *s);
int		parse_tex_id(const char *s, char **out);
int		parse_rgb(const char *s, t_rgb *out);
int		parse_num(const char *s, int *i);  // MISSING FUNCTION
void	push_map_line(t_vars *v, const char *s);
int		pad_map_rect(t_vars *v);
int		ft_rowlen(const char *s);
void	ft_fill_spaces(char *dst, int start, int end);
int		ft_pad_one_row(char **row_ptr, int width);
void	free_config(t_config *cfg);

/* ================= Utility Functions ================= */
int		is_ws(char c);
int		isnum(int c);
int		perr(const char *msg);
int		max(int a, int b);
void	ft_free(char **s, int j);
char	*strdup(const char *s);  // Add if not available
size_t	strlen(const char *s);   // Add if not available

/* ================= Validation Functions ================= */
int		validate_headers_complete(t_config *cfg);
int		validate_textures(t_config *cfg);
int		validate_colors(t_config *cfg);
int		validate_chars(t_vars *v);

/* ================= Player Validation ================= */
int		validate_and_extract_player(t_vars *v);
int		validate_and_extract_player_enhanced(t_vars *v);  // Alias to above

/* ================= Map Validation ================= */
int		validate_map_walls(t_vars *v);
int		validate_map_with_floodfill(t_vars *v);  // Alias to map_validation
int		map_validation(t_vars *var);  // Your actual function

/* ================= Map Character Checking ================= */
int		is_allowed(char c);
int		is_spawn(char c);
int		is_walkable(char c);
int		is_valid_map_char(char c);
int		is_surrounded_by_walls(t_vars *v, int y, int x);

/* ================= Flood Fill Functions ================= */
int		is_void_or_oob(t_vars *v, int y, int x);
int		flood_fill_recursive(char **map, int x, int y, t_vars *var);
char	**copy_map(char **map, int height);
int		warp_flood_fill(t_vars *var);

#endif