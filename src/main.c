/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:00:00 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/28 18:05:57 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char *sample_map[] = {
    "11111111111111111111111",
    "10000000001000000000001",
    "10110000111000000100001", 
    "10010000000000000100001",
    "10000000001000000000001",
    "10000N00000000000000001", // Player facing North
    "10000000001000000100001",
    "10110000111000000100001",
    "10010000000000000100001",
    "11111111111111111111111",
    NULL
};

void init_map_from_sample(t_game *g, t_cub *cub) 
{
    // Calculate map dimensions
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
    
    // Allocate memory for the map
    g->map = malloc(g->map_height * sizeof(char*));
    if (!g->map)
        return;
    
    int y = 0;
    while (y < g->map_height)
    {
        g->map[y] = malloc(g->map_width + 1);
        if (!g->map[y])
            return;
        
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
                g->xp_pos = x + 0.5f;
                g->yp_pos = y + 0.5f;
                g->facing_dir = c;
                g->map[y][x] = '0';
            }
            x++;
        }
        y++;
    }

    // Set texture paths - make sure these files exist!
    cub->dir->north_path = "./textures/pillar.png";
    cub->dir->south_path = "./textures/wall_1.png";
    cub->dir->east_path  = "./textures/bluestone.png";
    cub->dir->west_path  = "./textures/eagle.png";
}

void facing_dir_n_s(t_cub *cub)
{
    if (cub->game->facing_dir == 'N') 
    { 
        cub->game->dir_x = 0; 
        cub->game->dir_y = -1;
        cub->game->plane_x = 0.66f;
        cub->game->plane_y = 0;
    }
    else if (cub->game->facing_dir == 'S') 
    { 
        cub->game->dir_x = 0; 
        cub->game->dir_y = 1;
        cub->game->plane_x = -0.66f;
        cub->game->plane_y = 0;
    }
}

void facing_dir_e_w(t_cub *cub)
{
    if (cub->game->facing_dir == 'E') 
    {
        cub->game->dir_x = 1; 
        cub->game->dir_y = 0;
        cub->game->plane_x = 0;
        cub->game->plane_y = 0.66f;
    }
    else if (cub->game->facing_dir == 'W') 
    {
        cub->game->dir_x = -1;
        cub->game->dir_y = 0;
        cub->game->plane_x = 0;
        cub->game->plane_y = -0.66f;
    }
}

void    init_struct_element(t_cub *cub)
{
    cub->game->dir_x = 0;
    cub->game->xp_pos = 0;
    cub->game->dir_y = 0;
    cub->game->facing_dir = 'N';
    cub->game->yp_pos = 0;
    cub->game->plane_x = 0;
    cub->game->plane_y = 0;
    cub->textures->player = NULL;
    cub->textures->space = NULL;
    cub->textures->wall = NULL;
    cub->textures->pixel_ray = NULL;
    cub->textures->north = NULL;
    cub->textures->south = NULL;
    cub->textures->east = NULL;
    cub->textures->west = NULL;
}

int struct_init(t_cub *cub)
{
    cub->game = malloc(sizeof(t_game));
    cub->rays = malloc(sizeof(t_rays));
    cub->textures = malloc(sizeof(t_textures));
    cub->colors = malloc(sizeof(t_colors));
    cub->dir = malloc(sizeof(t_dir));
    if (!cub->game || !cub->rays || !cub->textures || !cub->colors || !cub->dir)
        return (1);
    init_struct_element(cub);
    return (0);
}

void free_map(t_game *game)
{
    if (game && game->map)
    {
        for (int i = 0; i < game->map_height; i++)
        {
            if (game->map[i])
                free(game->map[i]);
        }
        free(game->map);
        game->map = NULL;
    }
}

void free_textures(t_cub *cub)
{
    if (cub->textures)
    {
        if (cub->textures->north)
            mlx_delete_texture(cub->textures->north);
        if (cub->textures->south)
            mlx_delete_texture(cub->textures->south);
        if (cub->textures->east)
            mlx_delete_texture(cub->textures->east);
        if (cub->textures->west)
            mlx_delete_texture(cub->textures->west);
        if (cub->textures->pixel_ray)
            mlx_delete_image(cub->game->mlx, cub->textures->pixel_ray);
        if (cub->textures->player)
            mlx_delete_image(cub->game->mlx, cub->textures->player);
        if (cub->textures->wall) 
            mlx_delete_image(cub->game->mlx, cub->textures->wall);
    }
}

int ft_free_struct(t_cub *cub, int type)
{
    if (!cub)
        return (type);
    free_textures(cub);
    free_map(cub->game);
    if (cub->game && cub->game->mlx)
        mlx_terminate(cub->game->mlx);
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

int load_textures(t_cub *cub)
{
    cub->textures->north = mlx_load_png(cub->dir->north_path);
    cub->textures->south = mlx_load_png(cub->dir->south_path);
    cub->textures->east  = mlx_load_png(cub->dir->east_path);
    cub->textures->west  = mlx_load_png(cub->dir->west_path);
    if (!cub->textures->north || !cub->textures->south || 
        !cub->textures->east || !cub->textures->west)
    {
        printf("Error: Failed to load one or more textures\n");
        return (ft_free_struct(cub, 1));
    }
    return (0);
}

static uint32_t rgb_to_hex(int r, int g, int b)
{
    return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) |
           ((b & 0xFF) << 8)  | 0xFF;
}

void set_colors(t_cub *cub)
{    
    cub->colors->ceil[0] = 135; // R
    cub->colors->ceil[1] = 206; // G
    cub->colors->ceil[2] = 235; // B
    
    cub->colors->floor[0] = 34;  // R
    cub->colors->floor[1] = 139; // G
    cub->colors->floor[2] = 34;  // B

    cub->colors->ceil_col = rgb_to_hex(cub->colors->ceil[0], cub->colors->ceil[1], cub->colors->ceil[2]);
	cub->colors->floor_col = rgb_to_hex(cub->colors->floor[0], cub->colors->floor[1], cub->colors->floor[2]);
}

int init_image(t_cub *cub)
{
    cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
	if (!cub->textures->pixel_ray)
		return (1);
    cub->textures->wall = mlx_new_image(cub->game->mlx, 
            cub->game->map_width * TILE * MINIMAP_SCALE, cub->game->map_height * TILE * MINIMAP_SCALE);
    if (!cub->textures->wall)
		return (1);
    cub->textures->player = mlx_new_image(cub->game->mlx, P_SIZE * MINIMAP_SCALE, P_SIZE * MINIMAP_SCALE);
    if (!cub->textures->player)
        return (1);
    return 0;
}

int main(void)
{
    t_cub *cub;
    
    cub = malloc(sizeof(t_cub));
    if (!cub)
        return (1);
    if (struct_init(cub))
        return (ft_free_struct(cub, 1));
    init_map_from_sample(cub->game, cub);
    if (!cub->game->map)
        return (ft_free_struct(cub, 1));    
    facing_dir_n_s(cub);
    facing_dir_e_w(cub);
    set_colors(cub);
    cub->game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
    if (!cub->game->mlx)
        return (ft_free_struct(cub, 1));
    if (load_textures(cub))
        return (ft_free_struct(cub, 1));
    init_image(cub);
    draw_minimap(cub);

	mlx_image_to_window(cub->game->mlx, cub->textures->pixel_ray, 0, 0);
    mlx_image_to_window(cub->game->mlx, cub->textures->wall, 0, 0);
    mlx_loop_hook(cub->game->mlx, keyhook, cub);
    mlx_cursor_hook(cub->game->mlx, cursor, cub);
    // mlx_image_to_window(cub->game->mlx, cub->textures->player, (int)(cub->game->xp_pos * TILE * MINIMAP_SCALE), (int)(cub->game->yp_pos * TILE * MINIMAP_SCALE));
    if (ray(cub))
    return (ft_free_struct(cub, 1));
    mlx_loop(cub->game->mlx);
    return (ft_free_struct(cub, 0));
}
