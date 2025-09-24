#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../include/cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_void_or_oob(t_vars *v, int y, int x)
{
	if (y < 0 || y >= v->height || x < 0 || x >= v->width)
		return (1);
	return (v->map[y][x] == ' ');
}

static int	touches_void8(t_vars *v, int y, int x)
{
	int dy;
	int dx;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!(dy == 0 && dx == 0))
				if (is_void_or_oob(v, y + dy, x + dx))
					return (1);
			dx++;
		}
		dy++;
	}
	return (0);
}

int	flood_fill_recursive(char **map, int x, int y, int width, int height)
{
	char	current;

    if ((x < 0 || x >= width) || (y < 0 || y >= height))
        return (1);
    current = map[y][x];
    if (current == '1' || current == 'v')
        return (0);
    if (current == ' ')
        return (1);
    if (is_walkable(map[y][x]))
	{
        map[y][x] = 'v';
        if (flood_fill_recursive(map, x, y + 1, width, height))
			return (1);	while (i < var->height)
	{
		j = 0;
		while (j < var->width)
		{
			if (is_walkable(var->map[i][j]))
				if (touches_void8(var, i, j))
					return (1);
			j++;
		}
		i++;
	}
        if (flood_fill_recursive(map, x + 1, y, width, height))
			return (1);  
        if (flood_fill_recursive(map, x, y - 1, width, height))
			return (1);
        if (flood_fill_recursive(map, x - 1, y, width, height))
			return (1);
    }
    return (0);
}

static void	ft_free(char **s, int j)
{
	int i;

	i = 0;
	if (s != NULL)
	{
		if (j > 0)
		{
			while(i < j)
			{
				free(s[i]);
				i++;
			}
			free(s);
		}
		else
		{
			while(s[i])
			{
				free(s[i]);
				i++;
			}
			free(s);
		}
	}
}

char **copy_map(char **map, int height)
{
    char **new_map;
    int i;

    if (!map)
        return (NULL);
        
    new_map = malloc(sizeof(char *) * (height + 1));
    if (!new_map)
        return (NULL);
    
    i = 0;
    while (i < height)
    {
        new_map[i] = strdup(map[i]);
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

int warp_flood_fill(char **map, int x, int y, int width, int height)
{
    char	**new_map;
    int		result;

    new_map = copy_map(map, height);
    if (!new_map)
        return (1);
    result = flood_fill_recursive(new_map, x, y, width, height);
    ft_free(new_map, -1);
    return (result);
}
