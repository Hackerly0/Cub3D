#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../include/cub3d.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}




