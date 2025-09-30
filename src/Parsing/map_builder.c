/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:53:13 by hnisirat          #+#    #+#             */
/*   Updated: 2025/09/30 14:53:14 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	map_len(char **map)
{
	int	len;

	len = 0;
	if (!map)
		return (0);
	while (map[len])
		len++;
	return (len);
}

static int	copy_old(char **dst, char **src)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dst[i] = strdup(src[i]);
		if (!dst[i])
		{
			ft_free(dst, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	append_new(char **dst, int j, const char *s)
{
	dst[j] = strdup(s);
	if (!dst[j])
	{
		ft_free(dst, j);
		return (1);
	}
	dst[j + 1] = NULL;
	return (0);
}

static int	first_insert(t_vars *v, const char *s)
{
	char	**temp;

	temp = malloc(sizeof(char *) * 2);
	if (!temp)
		return (1);
	temp[0] = strdup(s);
	if (!temp[0])
	{
		free(temp);
		return (1);
	}
	temp[1] = NULL;
	v->map = temp;
	v->width = (int)strlen(s);
	v->height = 1;
	return (0);
}

static void	finalize_existing(t_vars *v, char **temp, const char *s, int len)
{
	ft_free(v->map, -1);
	v->map = temp;
	v->width = max(v->width, (int)strlen(s));
	v->height = len + 1;
}

void	push_map_line(t_vars *v, const char *s)
{
	int		len;
	char	**temp;

	if (!s)
		return ;
	if (!v->map)
	{
		first_insert(v, s);
		return ;
	}
	len = map_len(v->map);
	temp = malloc(sizeof(char *) * (len + 2));
	if (!temp)
		return ;
	if (copy_old(temp, v->map))
		return ;
	if (append_new(temp, len, s))
		return ;
	finalize_existing(v, temp, s, len);
}

static void	compute_dims(t_vars *v, int *height, int *maxw)
{
	int	y;
	int	w;

	*maxw = 0;
	y = 0;
	while (v->map[y])
	{
		w = ft_rowlen(v->map[y]);
		if (w > *maxw)
			*maxw = w;
		y++;
	}
	*height = y;
}

static int	pad_rows_to_width(t_vars *v)
{
	int	y;

	y = 0;
	while (v->map[y])
	{
		if (ft_pad_one_row(&v->map[y], v->width))
			return (1);
		y++;
	}
	return (0);
}

int	pad_map_rect(t_vars *v)
{
	int	h;
	int	maxw;

	if (!v || !v->map)
		return (0);
	compute_dims(v, &h, &maxw);
	v->height = h;
	if (v->width < maxw)
		v->width = maxw;
	if (pad_rows_to_width(v))
		return (1);
	return (0);
}
