/* Map validation functions */
#include "../include/cub3d.h"

int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' || 
            c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int is_surrounded_by_walls(t_vars *v, int y, int x)
{
    // Check if a '0' (floor) is properly surrounded by walls or other floors
    // A '0' next to a ' ' (space) or map edge is invalid
    
    if (y == 0 || y == v->height - 1 || x == 0 || x == v->width - 1)
    {
        if (v->map[y][x] == '0')
            return (0); // Floor at edge - invalid
    }
    
    // Check all 8 directions around floor tiles
    if (v->map[y][x] == '0')
    {
        int dy, dx;
        for (dy = -1; dy <= 1; dy++)
        {
            for (dx = -1; dx <= 1; dx++)
            {
                if (dy == 0 && dx == 0) continue;
                
                int ny = y + dy;
                int nx = x + dx;
                
                if (ny < 0 || ny >= v->height || nx < 0 || nx >= v->width)
                    return (0); // Out of bounds
                
                if (v->map[ny][nx] == ' ')
                    return (0); // Floor next to space - invalid
            }
        }
    }
    return (1);
}

int validate_map_walls(t_vars *v)
{
    int y, x;
    
    y = 0;
    while (y < v->height)
    {
        x = 0;
        while (x < v->width)
        {
            if (!is_surrounded_by_walls(v, y, x))
            {
                printf("Error\nMap is not properly enclosed by walls\n");
                return (1);
            }
            x++;
        }
        y++;
    }
    return (0);
}
