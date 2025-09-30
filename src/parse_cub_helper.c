/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:52:31 by hnisirat          #+#    #+#             */
/*   Updated: 2025/09/30 14:52:32 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	parse_tex_generic(const char *line, const char *id, char **path)
{
	if (starts_with_id(line, id))
	{
		if (*path)
		{
			printf("Error\nDuplicate %s texture\n", id);
			return (1);
		}
		if (parse_tex_id(line, path))
		{
			printf("Error\ninvalid %s\n", id);
			return (1);
		}
		return (0);
	}
	return (-1);
}

static int	parse_color_generic(const char *line, const char *id, t_rgb *rgb)
{
	if (starts_with_id(line, id))
	{
		if (rgb->r >= 0)
		{
			printf("Error\nDuplicate %s color\n", id);
			return (1);
		}
		if (parse_rgb(line, rgb))
		{
			printf("Error\ninvalid RGB for %s\n", id);
			return (1);
		}
		return (0);
	}
	return (-1);
}

int	handle_north_south(const char *line, t_config *cfg)
{
	int	r;

	r = parse_tex_generic(line, "NO", &cfg->textures.north.path);
	if (r != -1)
		return (r);
	r = parse_tex_generic(line, "SO", &cfg->textures.south.path);
	if (r != -1)
		return (r);
	return (-1);
}

int	handle_west_east(const char *line, t_config *cfg)
{
	int	r;

	r = parse_tex_generic(line, "WE", &cfg->textures.west.path);
	if (r != -1)
		return (r);
	r = parse_tex_generic(line, "EA", &cfg->textures.east.path);
	if (r != -1)
		return (r);
	return (-1);
}

int	handle_colors(const char *line, t_config *cfg)
{
	int	r;

	r = parse_color_generic(line, "F", &cfg->colors.floor);
	if (r != -1)
		return (r);
	r = parse_color_generic(line, "C", &cfg->colors.ceil);
	if (r != -1)
		return (r);
	return (-1);
}

int	handle_header_line(const char *line, t_config *cfg, int *phase)
{
	int	result;

	if (is_blank(line))
		return (0);
	result = handle_north_south(line, cfg);
	if (result >= 0)
		return (result);
	result = handle_west_east(line, cfg);
	if (result >= 0)
		return (result);
	result = handle_colors(line, cfg);
	if (result >= 0)
		return (result);
	if (is_map_line(line))
	{
		if (validate_headers_complete(cfg))
			return (1);
		*phase = 1;
		return (0);
	}
	printf("Error\nunknown identifier\n");
	return (1);
}
