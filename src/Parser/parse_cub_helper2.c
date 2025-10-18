/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:52:34 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/18 17:43:51 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../GNL/get_next_line.h"

int	drain_gnl(char *line, int fd)
{
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	handle_map_line(const char *line, t_config *cfg)
{
	if (is_blank(line))
	{
		if (cfg->vars.height == 0)
			return (0);
		cfg->vars.map_ended = 1;
		return (0);
	}
	if (cfg->vars.map_ended)
	{
		printf("Error\ncontent found after map end\n");
		return (1);
	}
	push_map_line(&cfg->vars, line);
	return (0);
}

int	process_file_lines(int fd, t_config *cfg)
{
	int		phase;
	char	*line;

	phase = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		rstrip_newline(line);
		if ((phase == 0 && process_phase0(line, cfg, &phase)))
		{
			free(line);
			return (drain_gnl(line, fd));
		}
		else if (phase == 1 && process_phase1(line, cfg))
			return (drain_gnl(line, fd));
		free(line);
	}
	return (0);
}

int	run_validations(t_config *cfg)
{
	if (!cfg->vars.map)
	{
		printf("Error\nno map found\n");
		return (1);
	}
	if (pad_map_rect(&cfg->vars))
		return (1);
	if (validate_chars(&cfg->vars))
		return (1);
	if (validate_and_extract_player(&cfg->vars))
		return (1);
	if (warp_flood_fill(&cfg->vars))
		return (1);
	if (map_validation(&cfg->vars))
		return (1);
	if (validate_door_accessibility(&cfg->vars))
		return (1);
	return (0);
}
