/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:58:30 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/08 16:30:05 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../GNL/get_next_line.h"

int	starts_with_id(const char *s, const char *id)
{
	int	i;

	i = 0;
	if (!s || !id)
		return (0);
	while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
		i++;
	return (ft_strncmp(s + i, id, ft_strlen(id)) == 0);
}

static void	parser_init(t_config *cfg)
{
	cfg->textures.north.path = NULL;
	cfg->textures.south.path = NULL;
	cfg->textures.west.path = NULL;
	cfg->textures.east.path = NULL;
	cfg->vars.map = NULL;
	cfg->vars.width = 0;
	cfg->vars.height = 0;
	cfg->vars.player.x = -1;
	cfg->vars.player.y = -1;
	cfg->vars.player.dir = 0;
	cfg->vars.map_ended = 0;
	cfg->colors.floor.r = -1;
	cfg->colors.floor.g = -1;
	cfg->colors.floor.b = -1;
	cfg->colors.ceil.r = -1;
	cfg->colors.ceil.g = -1;
	cfg->colors.ceil.b = -1;
}

static int	validate_inputs(const char *path, t_config *cfg)
{
	if (!path || !cfg)
		return (1);
	if (validate_cub_file(path))
		return (1);
	return (0);
}

static int	open_cub_fd(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		printf("Error\ncannot open file\n");
	return (fd);
}

int	parse_cub(const char *path, t_config *cfg)
{
	int	fd;
	int	result;

	parser_init(cfg);
	if (validate_inputs(path, cfg))
		return (1);
	fd = open_cub_fd(path);
	if (fd < 0)
		return (1);
	result = process_file_lines(fd, cfg);
	close(fd);
	if (result)
		return (result);
	return (run_validations(cfg));
}
