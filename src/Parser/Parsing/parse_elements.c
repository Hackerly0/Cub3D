/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:53:07 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/09 19:22:01 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	has_valid_extension(const char *path)
{
	size_t	len;

	len = strlen(path);
	if (len > 4 && strcmp(path + len - 4, ".png") == 0)
		return (1);
	return (0);
}

static int	validate_texture_file(const char *path)
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

static int	parse_component(const char *s, int *i, int *dst, int need_comma)
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

static char	*extract_and_trim_path(const char *s, int start)
{
	int		end;
	int		len;
	char	*path;

	end = start;
	while (s[end])
		end++;
	end--;
	while (end >= start && is_ws(s[end]))
		end--;
	len = end - start + 1;
	if (len <= 0)
		return (NULL);
	path = malloc(len + 1);
	if (!path)
		return (NULL);
	strncpy(path, s + start, len);
	path[len] = '\0';
	return (path);
}

int	parse_tex_id(const char *s, char **out)
{
	int		i;
	char	*path;

	i = 0;
	if (!s || !out)
		return (-1);
	while (is_ws(s[i]))
		i++;
	if (!isalpha(s[i]) || !isalpha(s[i + 1]))
		return (-1);
	i += 2;
	while (is_ws(s[i]))
		i++;
	if (s[i] == '\0')
		return (-1);
	path = extract_and_trim_path(s, i);
	if (!path)
		return (-1);
	if (validate_texture_file(path) < 0)
	{
		free(path);
		return (-1);
	}
	*out = path;
	return (0);
}

int	parse_rgb(const char *s, t_rgb *out)
{
	int	i;

	if (!s || !out)
		return (-1);
	i = 0;
	while (s[i] && is_ws(s[i]))
		i++;
	if (!isalpha(s[i]))
		return (-1);
	i++;
	while (s[i] && is_ws(s[i]))
		i++;
	if (!s[i])
		return (-1);
	if (parse_component(s, &i, &out->r, 1))
		return (-1);
	if (parse_component(s, &i, &out->g, 1))
		return (-1);
	if (parse_component(s, &i, &out->b, 0))
		return (-1);
	while (s[i] && is_ws(s[i]))
		i++;
	if (s[i])
		return (-1);
	return (0);
}

int	parse_num(const char *s, int *i)
{
	int	val;
	int	saw;

	val = 0;
	saw = 0;
	while (s[*i] && isnum(s[*i]))
	{
		saw = 1;
		val = val * 10 + (s[*i] - '0');
		(*i)++;
		if (val > 255)
			return (-1);
	}
	if (!saw)
		return (-1);
	return (val);
}

int	is_map_line(const char *s)
{
	int		i;
	char	c;

	i = 0;
	while (is_ws(s[i]))
		i++;
	c = s[i];
	if (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'D')
		return (1);
	return (0);
}
