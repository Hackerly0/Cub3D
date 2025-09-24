#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

int		parse_cub(const char *path, t_config *cfg);

int		is_map_line(const char *s);                 // first non-space in {0,1,N,S,E,W}
int		parse_tex_id(const char *s, char **out);    // NO/SO/WE/EA
int		parse_rgb(const char *s, t_rgb *out);       // F/C
void	push_map_line(t_vars *v, const char *s);    // store raw, update height/width
int		pad_map_rect(t_vars *v);
// Validation functions
int		validate_headers_complete(t_config *cfg);
int		validate_and_extract_player(t_vars *v);
int		validate_map_chars(t_vars *v);
int		validate_map_walls(t_vars *v);
// Flood fill validation
int		validate_map_with_floodfill(t_vars *v);
int		validate_and_extract_player_enhanced(t_vars *v);


#endif