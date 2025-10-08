/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 00:50:40 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/08 16:26:35 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <cub3d.h>
#include "../GNL/get_next_line.h"

static int	validate_file_extension(const char *path, const char *expected_ext)
{
	int	path_len;
	int	ext_len;

	if (!path || !expected_ext)
		return (1);
	path_len = (int)ft_strlen(path);
	ext_len = (int)ft_strlen(expected_ext);
	while (path_len > 0 && (path[path_len - 1] == ' '
			|| path[path_len - 1] == '\t'
			|| path[path_len - 1] == '\n'
			|| path[path_len - 1] == '\r'))
		path_len--;
	if (path_len < ext_len)
		return (1);
	return (ft_strncmp(path + (path_len - ext_len), expected_ext, ext_len) != 0);
}

static int	validate_texture_file(const char *path)
{
	if (!path)
		return (1);
	if (validate_file_extension(path, ".png"))
	{
		printf("Error\nTexture must be .png format: ");
		if (path)
			printf("%s\n", path);
		else
			printf("(null)\n");
		return (1);
	}
	return (0);
}

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
