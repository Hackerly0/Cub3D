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

#endif