/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:53:07 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/07 23:18:57 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

static char	*trim_whitespace(const char *str)
{
	int		start;
	int		end;
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && is_ws(str[start]))
		start++;
	end = start;
	while (str[end])
		end++;
	while (end > start && is_ws(str[end - 1]))
		end--;
	result = malloc(end - start + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (start < end)
		result[i++] = str[start++];
	result[i] = '\0';
	return (result);
}

int	parse_tex_id(const char *s, char **out)
{
	int	i;

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
	*out = trim_whitespace(s + i);
	if (!*out)
		return (-1);
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
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}
