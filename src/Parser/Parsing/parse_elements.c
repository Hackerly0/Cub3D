/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:53:07 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/18 14:39:56 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	if (validate_texture_file_path(path) < 0)
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
