/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:54:20 by hnisirat          #+#    #+#             */
/*   Updated: 2025/09/29 23:54:21 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <ctype.h>

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_colors
{
	t_rgb	ceil;
	t_rgb	floor;
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

typedef struct s_config
{
	t_colors		colors;
	t_directions	textures;
	t_vars			vars;
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

#endif