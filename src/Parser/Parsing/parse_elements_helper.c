/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:54:08 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/14 22:06:19 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_valid_extension(const char *path)
{
	size_t	len;

	len = strlen(path);
	if (len > 4 && strcmp(path + len - 4, ".png") == 0)
		return (1);
	return (0);
}

int	validate_texture_file_path(const char *path)
{
	int		fd;

	if (!path)
		return (-1);
	if (!has_valid_extension(path))
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

int	parse_component(const char *s, int *i, int *dst, int need_comma)
{
	int	v;

	v = parse_num(s, i);
	if (v < 0)
		return (-1);
	*dst = v;
	while (s[*i] && is_ws(s[*i]))
		(*i)++;
	if (need_comma)
	{
		if (s[*i] != ',')
			return (-1);
		(*i)++;
		while (s[*i] && is_ws(s[*i]))
			(*i)++;
	}
	return (0);
}
