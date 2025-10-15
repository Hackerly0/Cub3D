/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 00:50:40 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/15 16:12:51 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <cub3d.h>
#include "../GNL/get_next_line.h"

static int	validate_texture_var(t_config *cfg)
{
	if (validate_texture_file(cfg->textures.north.path))
		return (1);
	if (validate_texture_file(cfg->textures.south.path))
		return (1);
	if (validate_texture_file(cfg->textures.east.path))
		return (1);
	if (validate_texture_file(cfg->textures.west.path))
		return (1);
	return (0);
}

int	validate_textures(t_config *cfg)
{
	if (!cfg->textures.north.path)
	{
		printf("Error\nMissing North texture (NO)\n");
		return (1);
	}
	if (!cfg->textures.south.path)
	{
		printf("Error\nMissing South texture (SO)\n");
		return (1);
	}
	if (!cfg->textures.east.path)
	{
		printf("Error\nMissing East texture (EA)\n");
		return (1);
	}
	if (!cfg->textures.west.path)
	{
		printf("Error\nMissing West texture (WE)\n");
		return (1);
	}
	return (0);
}

int	validate_colors(t_config *cfg)
{
	if (cfg->colors.floor.r < 0 || cfg->colors.floor.g < 0
		|| cfg->colors.floor.b < 0)
	{
		printf("Error\nMissing or invalid Floor color (F)\n");
		return (1);
	}
	if (cfg->colors.ceil.r < 0 || cfg->colors.ceil.g < 0
		|| cfg->colors.ceil.b < 0)
	{
		printf("Error\nMissing or invalid Ceiling color (C)\n");
		return (1);
	}
	if (cfg->colors.floor.r > 255 || cfg->colors.floor.g > 255
		|| cfg->colors.floor.b > 255)
	{
		printf("Error\nFloor color values must be 0-255\n");
		return (1);
	}
	if (cfg->colors.ceil.r > 255 || cfg->colors.ceil.g > 255
		|| cfg->colors.ceil.b > 255)
	{
		printf("Error\nCeiling color values must be 0-255\n");
		return (1);
	}
	return (0);
}

int	validate_cub_file(const char *path)
{
	if (validate_file_extension(path, ".cub"))
	{
		printf("Error\nFile must have .cub extension\n");
		return (1);
	}
	return (0);
}

int	validate_headers_complete(t_config *cfg)
{
	if (validate_textures(cfg))
		return (1);
	if (validate_texture_var(cfg))
		return (1);
	if (validate_colors(cfg))
		return (1);
	return (0);
}
