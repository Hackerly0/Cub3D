#include <cub3d.h>

static void	set_player(t_vars *v, int x, int y, char c)
{
	v->player.x = x;
	v->player.y = y;
	v->player.dir = c;
	v->map[y][x] = '0';
}

int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_and_extract_player(t_vars *v)
{
	int		y;
	int		x;
	int		cnt;
	char	c;

	if (!v || !v->map)
		return (1);
	cnt = 0;
	y = 0;
	while (y < v->height)
	{
		x = 0;
		while (x < v->width)
		{
			c = v->map[y][x];
			if (is_spawn(c) && ++cnt)
				if (cnt > 1)
					return (1);
			if (cnt == 1 && is_spawn(c))
				set_player(v, x, y, c);
			x++;
		}
		y++;
	}
	return (cnt != 1);
}
