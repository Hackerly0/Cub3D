#include <cub3d.h>

void    push_map_line(t_vars *v, const char *s)
{
	int		i;
	int		j;
	int		len;
	char	**temp;

	i = 0;
	j = 0;
	len = 0;
	if (!s)
		return ;
	while (v->map && v->map[len]) 
		len++;
	temp = malloc(sizeof(char *) * (len + 2));
	if (!temp)
		return ;
	if (v->map)
	{
		while (v->map[i])
		{
			temp[j] = strdup(v->map[i]);
			if (!temp[j])
			{
				ft_free(temp, j);
				return ;	
			}
			i++;
			j++;
		}
		temp[j++] = strdup(s);
		if (!temp[j-1])
		{
			ft_free(temp, j - 1);
			return ;	
		}
		temp[j] = NULL;
		ft_free(v->map, -1);
		v->width = max(v->width, (int)strlen(s));
		v->height = len + 1;
		v->map = temp;
	}
	else
	{
		temp[0] = strdup(s);
		if (!temp[0])
		{
			free(temp);
			return ;
		}
		temp[1] = NULL;
		v->map = temp;
		v->width = strlen(s);
		v->height = 1;
	}
}

int	pad_map_rect(t_vars *v)
{
	int	y;
	int	maxw;

	if (!v || !v->map)
		return (0);
	maxw = 0;
	y = 0;
	while (v->map[y])
	{
		if (ft_rowlen(v->map[y]) > maxw)
			maxw = ft_rowlen(v->map[y]);
		y++;
	}
	v->height = y;
	if (v->width < maxw)
		v->width = maxw;
	y = 0;
	while (v->map[y])
	{
		if (ft_pad_one_row(&v->map[y], v->width))
			return (1);
		y++;
	}
	return (0);
}
