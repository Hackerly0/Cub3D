/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:18:04 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/13 14:58:27 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

#define BPP sizeof(int32_t)

char *sample_map[] = {
    "1111111111111111111",
    "10N000000001111111",
    "1001000000000111111", 
    "10000000000001",
    "1 000001", // Player facing North
    "10111001",
    "101 100001",
    "111 1111",
    NULL
};

void init_map_from_muhammed(t_game *g) 
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
}

#define TILE 64
#define P_SIZE 10

void    dda(t_cub *cub, mlx_image_t* pixel_ray)
{
    if (fabs(cub->rays->m) <= 1)
    {
        while (cub->rays->x_new < cub->rays->x_end)
        {
            mlx_put_pixel(pixel_ray, (int)roundf(cub->rays->x_new), (int)roundf(cub->rays->y_new), 0xFF0000FF);
            cub->rays->x_new += 1;
            cub->rays->y_new += cub->rays->m;
        }
    }
    else
    {
        while (cub->rays->y_new < cub->rays->y_end)
        {
            mlx_put_pixel(pixel_ray, (int)roundf(cub->rays->x_new), (int)roundf(cub->rays->y_new), 0xFF0000FF);
            cub->rays->y_new += 1;
            cub->rays->x_new += 1.0f / cub->rays->m;
        }
    }
}

int    ray(t_cub *cub)
{
    cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
    if (!cub->textures->pixel_ray)
        return (1);
    mlx_image_to_window(cub->game->mlx, cub->textures->pixel_ray, 0, 0);
    cub->rays->x_end = cub->game->xp_pos * TILE + 200;
    cub->rays->y_end = cub->game->yp_pos * TILE + 100;
    cub->rays->m = (cub->rays->y_end - (cub->game->yp_pos * TILE)) / (cub->rays->x_end - (cub->game->xp_pos * TILE));
    cub->rays->x_new = cub->game->xp_pos * TILE;
    cub->rays->y_new = cub->game->yp_pos * TILE;
    dda(cub, cub->textures->pixel_ray);
    return (0);
}

int    player(t_game *game, t_cub *cub)
{
    int i;
    int j;
    int px;
    int py;

    cub->textures->player = mlx_new_image(game->mlx, P_SIZE, P_SIZE);
    if (!cub->textures->player)
        return (1);
    i = 0;
    while (i < P_SIZE)
    {
        j = 0;
        while (j < P_SIZE)
        {
            mlx_put_pixel(cub->textures->player, j, i, 0x00FF00FF);
            j++;
        }
        i++;
    }
    px = (int)(game->xp_pos * TILE);
    py = (int)(game->yp_pos * TILE);
    mlx_image_to_window(game->mlx, cub->textures->player, px, py);
    return (0);
}

int struct_init(t_cub *cub)
{
    cub->game = malloc(sizeof(t_game));
    cub->rays = malloc(sizeof(t_rays));
    cub->textures = malloc(sizeof(t_textures));
    if (!cub->game || !cub->rays || !cub->textures)
        return (1);
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
    free(cub);
    return (type);
}

int    draw_map(t_cub *cub)
{
    int i;
    int j;
    
    cub->textures->wall = mlx_new_image(cub->game->mlx, TILE, TILE);
    if (!cub->textures->wall)
        return (1);
    memset(cub->textures->wall->pixels, 255, cub->textures->wall->width * cub->textures->wall->height * BPP);
    i = 0;
    while (i < cub->game->map_height)
    {
        j = 0;
        while (j < cub->game->map_width)
        {
            if (cub->game->map[i][j] == '1')
                mlx_image_to_window(cub->game->mlx, cub->textures->wall, j * TILE, i * TILE);
            j++;
        }
        i++;
    }
    return (0);
}
void mouse_event(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
    (void)mods;  // إذا ما بدك تستخدمها
    (void)param;
    if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
        printf("Left click!\n");
}
int main()
{
    t_cub *cub;

    cub = malloc(sizeof(t_cub));
    if (!cub)
        return (1);
    if (struct_init(cub))
        return (ft_free_struct(cub, 1));
    init_map_from_muhammed(cub->game);
    cub->game->mlx = mlx_init(WIDTH, cub->game->map_height * TILE, "Cub3D", true);
    if (!cub->game->mlx)
        return (ft_free_struct(cub, 1));
    if (draw_map(cub))
        return (ft_free_struct(cub, 1));
    if (player(cub->game, cub))
        return (ft_free_struct(cub, 1));
    if (ray(cub))
        return (ft_free_struct(cub, 1));
    mlx_mouse_hook(cub->game->mlx, &mouse_event, cub->game->mlx);

    mlx_loop(cub->game->mlx);
    mlx_terminate(cub->game->mlx);
    return (0);
}
