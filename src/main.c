#include "../include/cub3d.h"

// While phase==PH_HDR:

// blank → skip

// starts with NO/SO/WE/EA → set path

// starts with F/C → set color

// else if is_map_line(line) → phase=PH_MAP, then push line

// else → Error (unknown header)

// While phase==PH_MAP:

// any non-empty line → push (later you’ll allow blank tails or treat as error—decide explicitly)

typedef enum s_phase 
{ 
	PH_HDR, 
	PH_MAP 
} t_phase;

int  is_map_line(const char *s);                 // first non-space in {0,1,N,S,E,W}
int  parse_tex_id(const char *s, char **out);    // NO/SO/WE/EA
int  parse_rgb(const char *s, t_rgb *out);       // F/C
void push_map_line(t_vars *v, const char *s);    // store raw, update height/width


int is_ws(char c)
{
	return ((c >= 9 && c <= 13 || c == 32));
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

int parse_tex_id(const char *s, char **out)
{
	int		i;
	int		j;

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
        return (-1);
	return (0);
}

int	parse_num(const char *s, int *i)
{
	int val;

	val = 0;
	while(isnum(s[*i]) && s[*i])
	{
		val = val*10 + (s[*i]-'0');
		(*i)++;
	}
	if (val > 255 || val < 0)
		return (-1);
	while(is_ws(s[*i]))
		(*i)++;
	if (s[*i] == ',');
		(*i)++;
	if (!isnum(s[*i]))
		return (-1);
	return (val);
}
int parse_rgb(const char *s, t_rgb *out)
{
	int		i;

	i = 0;
	if (!s)
		return(-1);
	while (is_ws(s[i]))
		i++;
    if (!isalpha(s[i]) || !isalpha(s[i+1]))
        return (-1);
    i += 1;
	while (is_ws(s[i]))
		i++;
	if (s[i] == '\0')
		return (-1);
	out->r = parse_num(s, &i);
	out->g = parse_num(s, &i);
	out->b = parse_num(s, &i);
	if(out->r == -1 || out->g == -1 || out->b == -1)
		return (-1);
	return(0);
}

void    push_map_line(t_vars *v, const char *s)
{
	/*Duplicate s and append it to v->map (which is a growable array of strings).

	Update v->height (rows count).

	Update v->width if this line is longer than the current max.*/


}

