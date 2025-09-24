/* charset_spawn.c */
#include "cub3d.h"

static int	is_allowed(char c)
{
	return (c == '0' || c == '1' || c == ' ' ||
		c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* Return 0 on success, 1 on error.
   Outputs spawn (sx, sy, sdir). Requires map to be padded. */
// int	validate_charset_and_spawn(t_vars *v, int *sx, int *sy, char *sdir)
// {
// 	int	y;
// 	int	x;
// 	int	found;

// 	if (!v || !v->map || !sx || !sy || !sdir)
// 		return (1);
// 	found = 0;
// 	y = 0;
// 	while (y < v->height)
// 	{
// 		x = 0;
// 		while (x < v->width)
// 		{
// 			if (!is_allowed(v->map[y][x]))
// 				return (1); /* Error: invalid char */
// 			if (is_spawn(v->map[y][x]))
// 			{
// 				if (found)
// 					return (1); /* Error: multiple spawns */
// 				found = 1;
// 				*sx = x;
// 				*sy = y;
// 				*sdir = v->map[y][x];
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	if (!found)
// 		return (1); /* Error: no spawn */
// 	return (0);
// }

int	map_validation(t_vars *var)
{
	int	spawn;
	int	i;
	int	j;

	spawn = 0;
	i = 0;
	while (i < var->height)
	{
		j = 0;
		while (j < var->width)
		{
			if (!is_allowed(var->map[i][j]))
				return (1);
			if (is_spawn(var->map[i][j]))
			{
				spawn++;
				var->player.x = j;
				var->player.y = i;
				var->player.dir = var->map[i][j];
			}
			if (is_spawn(var->map[i][j]) && ++spawn > 1)
  			  return (1);

			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (i < var->height)
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
	return (0);
}

typedef struct s_vars
{
	char     **map;   // 2D array of map (padded)
	int       width;  // max map width
	int       height; // number of map rows
	t_player  player;
}   t_vars;
