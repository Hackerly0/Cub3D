/* Add this function to validate and extract player position */
#include "../include/cub3d.h"

int validate_and_extract_player(t_vars *v)
{
    int y, x, player_count;
    
    player_count = 0;
    y = 0;
    while (y < v->height)
    {
        x = 0;
        while (x < v->width)
        {
            char c = v->map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                player_count++;
                v->player.x = x + 0.5; // center of cell
                v->player.y = y + 0.5;
                v->player.dir = c;
                v->map[y][x] = '0'; // replace with floor
            }
            x++;
        }
        y++;
    }

    if (player_count != 1)
    {
        printf("Error\nMap must contain exactly one player (N/S/E/W)\n");
        return (1);
    }
    return (0);
}
