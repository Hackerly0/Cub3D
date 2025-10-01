/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:00:00 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/01 20:02:32 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// char *sample_map[] = {
//     "11111111111111111111111",
//     "10000000001000000000001",
//     "10110000111000000100001", 
//     "10010000000000000100001",
//     "10000000001000000000001",
//     "10000E0000D000000000001", // Player facing North
//     "10000000001000000100001",
//     "101100001D1000000100001",
//     "100D0000000000000D00001",
//     "10010000000000000100001",
//     "10010000000000000100001",
//     "11111111111111111111111",
//     NULL
// };

// void init_map_from_sample(t_game *g, t_cub *cub) 
// {
//     // Calculate map dimensions
//     g->map_height = 0;
//     while (sample_map[g->map_height]) 
//         g->map_height++;
    
//     // Find the maximum width across all rows
//     g->map_width = 0;
//     int i = 0;
//     while (i < g->map_height) {
//         int len = strlen(sample_map[i]);
//         if (len > g->map_width) 
//             g->map_width = len;
//         i++;
//     }
    
//     // Allocate memory for the map
//     g->map = malloc(g->map_height * sizeof(char*));
//     if (!g->map)
//         return;
    
//     int y = 0;
//     while (y < g->map_height)
//     {
//         g->map[y] = malloc(g->map_width + 1);
//         if (!g->map[y])
//             return;
        
//         // Copy the row and pad with '1' if necessary
//         strcpy(g->map[y], sample_map[y]);
//         int current_len = strlen(sample_map[y]);
//         while (current_len < g->map_width)
//         {
//             g->map[y][current_len] = '1';
//             current_len++;
//         }
//         g->map[y][g->map_width] = '\0';
    
//         int x = 0;
//         while (x < g->map_width) {
//             char c = g->map[y][x];
//             if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
//                 g->xp_pos = x + 0.5f;
//                 g->yp_pos = y + 0.5f;
//                 g->facing_dir = c;
//                 g->map[y][x] = '0';
//             }
//             x++;
//         }
//         y++;
//     }

//     // Set texture paths - make sure these files exist!
//     // cub->dir->north_path = "./textures/pillar.png";
//     // cub->dir->south_path = "./textures/wall_1.png";
//     // cub->dir->east_path  = "./textures/bluestone.png";
//     // cub->dir->west_path  = "./textures/eagle.png";
//     cub->dir->door_path  = "./textures/door.png";
// }

int is_valid_position(t_cub *cub, float map_x, float map_y)
{
	char cell;

	cell = cub->game->map[(int)map_y][(int)map_x];
    if (map_x < 0 || map_x >= cub->game->map_width || 
        map_y < 0 || map_y >= cub->game->map_height)
        return 0;
    if (cell == '1')
        return 0;
    if (cell == 'D' && cub->game->door_state[(int)map_y][(int)map_x] == '1')
        return 0;
    return 1;
}

int load_textures(t_cub *cub)
{
    cub->textures->north = mlx_load_png(cub->dir->north_path);
    cub->textures->south = mlx_load_png(cub->dir->south_path);
    cub->textures->east  = mlx_load_png(cub->dir->east_path);
    cub->textures->west  = mlx_load_png(cub->dir->west_path);
    cub->textures->door  = mlx_load_png("./textures/door.png");
    if (!cub->textures->north || !cub->textures->south ||
        !cub->textures->east || !cub->textures->west || !cub->textures->door)
    {
        printf("Error: Failed to load one or more textures\n");
        return (ft_free_struct(cub, 1));
    }
    return (0);
}

int	raycasting(t_cub *cub)
{
	cub->game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!cub->game->mlx)
		return (ft_free_struct(cub, 1));
	if (load_textures(cub))
		return (ft_free_struct(cub, 1));
	if (init_image(cub))
		return (ft_free_struct(cub, 1));
	chosse_scale(cub);
	draw_minimap(cub);
	player_minimap(cub);
	mlx_image_to_window(cub->game->mlx, cub->textures->pixel_ray, 0, 0);
	mlx_image_to_window(cub->game->mlx, cub->textures->wall, 0, 0);
	mlx_image_to_window(cub->game->mlx, cub->textures->player,
		(int)(cub->game->xp_pos * cub->game->minimap_scale)
		- (P_SIZE * cub->game->minimap_scale) / 2,
		(int)(cub->game->yp_pos * cub->game->minimap_scale)
		- (P_SIZE * cub->game->minimap_scale) / 2);
	mlx_loop_hook(cub->game->mlx, keyhook, cub);
	mlx_cursor_hook(cub->game->mlx, cursor, cub);
	if (ray(cub))
		return (ft_free_struct(cub, 1));
	mlx_loop(cub->game->mlx);
	return (ft_free_struct(cub, 0));
}
