#include <cub3d.h>
#include "../GNL/get_next_line.h"

static int	process_phase0(char *line, t_config *cfg, int *phase)
{
	int	result;

	result = handle_header_line(line, cfg, &(*phase));
	if (result)
	{
		free(line);
		return (result);
	}
	return (0);
}

static int	process_phase1(char *line, t_config *cfg)
{
	int	result;

	result = handle_map_line(line, cfg);
	if (result)
	{
		free(line);
		return (result);
	}
	return (0);
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
		if (phase == 0 && process_phase0(line, cfg, &phase))
			return (1);
		if (phase == 1 && process_phase1(line, cfg))
			return (1);
		free(line);
	}
	return (0);
}

static void	print_padded_map(t_vars *v)
{
	int	i;

	printf("DEBUG: Padded map:\n");
	i = 0;
	while (i < v->height)
	{
		printf("'%s'\n", v->map[i]);
		i++;
	}
}

static void	print_success(t_config *cfg)
{
	printf("All validations passed!\n");
	printf("Player at (%d, %d) facing '%c'\n",
		(int)cfg->vars.player.x,
		(int)cfg->vars.player.y,
		cfg->vars.player.dir);
}

int	run_validations(t_config *cfg)
{
	if (!cfg->vars.map)
	{
		printf("Error\nno map found\n");
		return (1);
	}
	if (pad_map_rect(&cfg->vars))
	{
		printf("Error\nalloc failed while padding\n");
		return (1);
	}
	print_padded_map(&cfg->vars);
	if (validate_chars(&cfg->vars))
		return (1);
	if (validate_and_extract_player(&cfg->vars))
		return (1);
	if (warp_flood_fill(&cfg->vars))
		return (1);
	if (map_validation(&cfg->vars))
		return (1);
	print_success(cfg);
	return (0);
}
