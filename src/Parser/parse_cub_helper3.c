/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_helper3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:22:41 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/14 22:01:13 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_blank(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
		i++;
	return (s[i] == '\0');
}

void	rstrip_newline(char *s)
{
	int	n;

	if (!s)
		return ;
	n = (int)ft_strlen(s);
	while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
	{
		s[n - 1] = '\0';
		n--;
	}
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

int	process_phase0(char *line, t_config *cfg, int *phase)
{
	int	result;

	result = handle_header_line(line, cfg, &(*phase));
	if (result)
	{
		free_config(cfg);
		return (result);
	}
	return (0);
}

int	process_phase1(char *line, t_config *cfg)
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
