/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:53:02 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/18 17:12:13 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_rows(char **s, int count)
{
	int	i;

	i = 0;
	if (count >= 0)
	{
		while (i < count)
		{
			free(s[i]);
			i++;
		}
	}
	else
	{
		while (s[i])
		{
			free(s[i]);
			i++;
		}
	}
}

void	ft_free(char **s, int j)
{
	if (!s)
		return ;
	free_rows(s, j);
	free(s);
}

char	**copy_map(char **map, int height)
{
	char	**new_map;
	int		i;

	if (!map)
		return (NULL);
	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
		{
			ft_free(new_map, i);
			return (NULL);
		}
		i++;
	}
	new_map[height] = NULL;
	return (new_map);
}

void	free_config(t_config *cfg)
{
	if (!cfg)
		return ;
	if (cfg->textures.north.path)
		free(cfg->textures.north.path);
	if (cfg->textures.south.path)
		free(cfg->textures.south.path);
	if (cfg->textures.west.path)
		free(cfg->textures.west.path);
	if (cfg->textures.east.path)
		free(cfg->textures.east.path);
	ft_free(cfg->vars.map, -1);
	cfg->textures.north.path = NULL;
	cfg->textures.south.path = NULL;
	cfg->textures.west.path = NULL;
	cfg->textures.east.path = NULL;
	cfg->vars.map = NULL;
}
