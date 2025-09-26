#include "../include/cub3d.h"
#include <ctype.h>

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


void	ft_free(char **s, int j)
{
	int i;

	if (!s)
		return ;
	i = 0;
	if (j != -1)
	{
		while(i < j)
		{
			free(s[i]);
			s[i] = NULL;
			i++;
		}
	}
	else
	{
		while(s[i])
		{
			free(s[i]);
			s[i] = NULL;
			i++;
		}
	}
	free(s);
	s = NULL;
}


