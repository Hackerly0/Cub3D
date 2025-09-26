#include <cub3d.h>

int parse_tex_id(const char *s, char **out)
{
	int		i;

	i = 0;
	if (!s)
		return(-1);
	while (is_ws(s[i]))
		i++;
    if (!isalpha(s[i]) || !isalpha(s[i+1]))
        return (-1);
    i += 2;
	while (is_ws(s[i]))
		i++;
	if (s[i] == '\0')
		return (-1);
	*out = strdup(s + i);

    if (!*out)
	{
        return (-1);
	}
	return (0);
}

int	parse_rgb(const char *s, t_rgb *out)
{
	int	i;
	int	v;

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

	/* R */
	v = parse_num(s, &i);
	if (v < 0)
		return (-1);
	out->r = v;
	while (s[i] && is_ws(s[i]))
		i++;
	if (s[i] != ',')
		return (-1);
	i++;
	while (s[i] && is_ws(s[i]))
		i++;

	/* G */
	v = parse_num(s, &i);
	if (v < 0)
		return (-1);
	out->g = v;
	while (s[i] && is_ws(s[i]))
		i++;
	if (s[i] != ',')
		return (-1);
	i++;
	while (s[i] && is_ws(s[i]))
		i++;

	/* B */
	v = parse_num(s, &i);
	if (v < 0)
		return (-1);
	out->b = v;
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

int is_map_line(const char *s)
{
	int i;

	i = 0;
	while (is_ws(s[i]))
		i++;
	if (s[i] == '0')
		return (1);
	else if (s[i] == '1')
		return (1);
	else if (s[i] == 'N')
		return (1);
	else if (s[i] == 'S')
		return (1);
	else if (s[i] == 'E')
		return (1);
	else if (s[i] == 'W')
		return (1);
	return (0);
}
