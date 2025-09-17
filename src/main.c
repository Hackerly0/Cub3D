/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:18:04 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/17 18:35:51 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define FOV 60

#define BPP sizeof(int32_t)

char *sample_map[] = {
    "1111111111111111111",
    "100000000001111111",
    "100N000000000111111", 
    "10000000000001",
    "1 000001", // Player facing North
    "10111001",
    "101 100001",
    "111 1111",
    NULL
};

void init_map_from_muhammed(t_game *g, t_cub *cub) 
{
    /////
    g->map_height = 0;
    while (sample_map[g->map_height]) 
        g->map_height++;
    
    // Find the maximum width across all rows
    g->map_width = 0;
    int i = 0;
    while (i < g->map_height) {
        int len = strlen(sample_map[i]);
        if (len > g->map_width) 
            g->map_width = len;
        i++;
    }
    //////


    
    g->map = malloc(g->map_height * sizeof(char*));
    int y = 0;
    while (y < g->map_height)
    {
        g->map[y] = malloc(g->map_width + 1);
        
        // Copy the row and pad with '1' if necessary
        strcpy(g->map[y], sample_map[y]);
        int current_len = strlen(sample_map[y]);
        while (current_len < g->map_width)
        {
            g->map[y][current_len] = '1';
            current_len++;
        }
        g->map[y][g->map_width] = '\0';
    
        int x = 0;
        while (x < g->map_width) {
            char c = g->map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
                g->xp_pos = x + 0.5;//x + 0.5;
                g->yp_pos = y + 0.5;//y + 0.5;
                g->facing_dir = c;
                g->map[y][x] = '0';
            }
            x++;
        }
        y++;
    }

    cub->dir->north_path = "./textures/pillar.png";
    cub->dir->south_path = "./textures/wall_1.png";
    cub->dir->east_path  = "./textures/bluestone.png";
    cub->dir->west_path  = "./textures/eagle.png";
}

void    facing_dir(t_cub *cub)
{
    if (cub->game->facing_dir == 'N') 
    { 
        cub->game->dir_x = 0; 
        cub->game->dir_y = -1; 
    }
    if (cub->game->facing_dir == 'S') 
    { 
        cub->game->dir_x = 0; 
        cub->game->dir_y = 1; 
    }
    if (cub->game->facing_dir == 'E') 
    {
        cub->game->dir_x = 1; 
        cub->game->dir_y = 0; 
    }
    if (cub->game->facing_dir == 'W') 
    {
        cub->game->dir_x = -1;
        cub->game->dir_y = 0; 
    }
}
int ft_free_struct(t_cub *cub, int type);

int struct_init(t_cub *cub)
{
    cub->game = malloc(sizeof(t_game));
    cub->rays = malloc(sizeof(t_rays));
    cub->textures = malloc(sizeof(t_textures));
    cub->colors = malloc(sizeof(t_colors));
    cub->dir = malloc(sizeof(t_dir));
    if (!cub->game || !cub->rays || !cub->textures || !cub->colors || !cub->dir)
        return (1);
    cub->game->dir_x = 0;
    cub->game->xp_pos = 0;
    cub->game->dir_y = 0;
    cub->game->facing_dir = 'N';
    cub->game->yp_pos = 0;
    cub->rays->y_new = 0;
    cub->rays->x_new = 0;
    cub->rays->y_end = 0;
    cub->rays->x_end = 0;
    cub->textures->player = NULL;
    cub->rays->m = 0;
    cub->textures->wall = NULL;
    cub->textures->pixel_ray = NULL;
    return (0);
}

int ft_free_struct(t_cub *cub, int type)
{
    if (cub->game)
        free(cub->game);
    if (cub->rays)
        free(cub->rays);
    if (cub->textures)
        free(cub->textures);
    if (cub->colors)
        free(cub->colors);
    if (cub->dir)
        free(cub->dir);
    free(cub);
    return (type);
}

int main()
{
    t_cub *cub;

    cub = malloc(sizeof(t_cub));
    if (!cub)
        return (1);
    if (struct_init(cub))
        return (ft_free_struct(cub, 1));
    init_map_from_muhammed(cub->game, cub);
    facing_dir(cub);
    cub->textures->north = mlx_load_png(cub->dir->north_path);
    cub->textures->south = mlx_load_png(cub->dir->south_path);
    cub->textures->east  = mlx_load_png(cub->dir->east_path);
    cub->textures->west  = mlx_load_png(cub->dir->west_path);
    if (!cub->textures->north || !cub->textures->south || !cub->textures->east || !cub->textures->west)
    {
        ft_free_struct(cub, 1);
        return 1;
    }
    cub->game->mlx = mlx_init(WIDTH, cub->game->map_height * TILE, "Cub3D", true);
    if (!cub->game->mlx)
        return (ft_free_struct(cub, 1));
    // if (draw_map(cub))
    //     return (ft_free_struct(cub, 1));
    // if (player(cub->game, cub))
    //     return (ft_free_struct(cub, 1));
    if (ray(cub))
        return (ft_free_struct(cub, 1));
    mlx_key_hook(cub->game->mlx, my_keyhook, cub);
    mlx_loop(cub->game->mlx);
    mlx_terminate(cub->game->mlx);
    return (0);
}
