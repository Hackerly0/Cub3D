/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:18:04 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/15 14:11:39 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define FOV 60

#define BPP sizeof(int32_t)

char *sample_map[] = {
    "1111111111111111111",
    "10N000000001111111",
    "1001000010000111111", 
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


static void	init_dda(t_cub *cub, float *x_inc, float *y_inc, float *steps)//should understand
{
    float dx;
    float dy;
    float abs_dx;
    float abs_dy;

    dx = cub->rays->x_end - cub->rays->x_new;
    dy = cub->rays->y_end - cub->rays->y_new;
    abs_dx = dx;
    if (abs_dx < 0)
        abs_dx = -abs_dx;
    abs_dy = dy;
    if (abs_dy < 0)
        abs_dy = -abs_dy;
    *steps = abs_dx;
    if (abs_dy > abs_dx)
        *steps = abs_dy;
    if (*steps == 0)
        *steps = 1;
    *x_inc = dx / *steps;
    *y_inc = dy / *steps;
}

void    print_ray(float steps, t_cub *cub, float x_inc, float y_inc)
{
    int i;
    int px;
    int py;

    i = 0;
    while (i <= (int)steps)
    {
        px = (int)(cub->rays->x_new + 0.5f);
        py = (int)(cub->rays->y_new + 0.5f);
        if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
            mlx_put_pixel(cub->textures->pixel_ray, px, py, 0xFF0000FF);
        cub->rays->x_new += x_inc;
        cub->rays->y_new += y_inc;
        i++;
    }
}

void	dda(t_cub *cub)
{

    float x_inc;
    float y_inc;
    float steps;

    init_dda(cub, &x_inc, &y_inc, &steps);
    print_ray(steps, cub, x_inc, y_inc);
}

// int    ray(t_cub *cub)
// {    
//     cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
//     if (!cub->textures->pixel_ray)
//         return (1);
//     mlx_image_to_window(cub->game->mlx, cub->textures->pixel_ray, 0, 0);
    
//     float ray_length = 200;
//     cub->rays->x_end = cub->game->xp_pos * TILE + cub->game->dir_x * ray_length;
//     cub->rays->y_end = cub->game->yp_pos * TILE + cub->game->dir_y * ray_length;
//     cub->rays->m = (cub->rays->y_end - (cub->game->yp_pos * TILE)) / (cub->rays->x_end - (cub->game->xp_pos * TILE));
//     cub->rays->x_new = cub->game->xp_pos * TILE;
//     cub->rays->y_new = cub->game->yp_pos * TILE;
//     dda(cub);
    
//     return (0);
// }
int ray(t_cub *cub)
{
    int     i;
    float   fov_rad;
    float   start_angle;
    float   step_angle;

    cub->textures->pixel_ray = mlx_new_image(cub->game->mlx, WIDTH, HEIGHT);
    if (!cub->textures->pixel_ray)
        return (1);
    mlx_image_to_window(cub->game->mlx, cub->textures->pixel_ray, 0, 0);
    fov_rad = 60.0f * M_PI / 180.0f;
    start_angle = atan2f(cub->game->dir_y, cub->game->dir_x) - fov_rad / 2.0f;
    step_angle = fov_rad / (float)WIDTH;
    i = 0;
    while (i < WIDTH)
    {
        cub->rays->x_new = cub->game->xp_pos * TILE;
        cub->rays->y_new = cub->game->yp_pos * TILE;
        cub->rays->x_end = cub->rays->x_new + cosf(start_angle + i * step_angle) * 200;
        cub->rays->y_end = cub->rays->y_new + sinf(start_angle + i * step_angle) * 200;
        dda(cub);
        i++;
    }
    return (0);
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

void rotate_player(t_cub *cub, float theta)
{
    float old_dir_x;
    old_dir_x = cub->game->dir_x;
    cub->game->dir_x = cub->game->dir_x * cos(theta) - cub->game->dir_y * sin(theta);
    cub->game->dir_y = old_dir_x * sin(theta) + cub->game->dir_y * cos(theta);

    // 2️⃣ تدوير مستوى الكاميرا (plane_x, plane_y) إذا تستخدم raycasting
    // float old_plane_x = cub->game->plane_x;
    // cub->game->plane_x = cub->game->plane_x * cos(theta) - cub->game->plane_y * sin(theta);
    // cub->game->plane_y = old_plane_x * sin(theta) + cub->game->plane_y * cos(theta);
}

void my_keyhook(mlx_key_data_t keydata, void *structs)
{
    t_cub *cub;
    
    cub = (t_cub *)structs;
    if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        rotate_player(cub, -0.05f);
    if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        rotate_player(cub, 0.05f);
    if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        cub->game->yp_pos -= 0.2;
    if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        cub->game->yp_pos += 0.2;
    if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        cub->game->xp_pos -= 0.2;
    if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        cub->game->xp_pos += 0.2;
    if (cub->textures->pixel_ray)
        mlx_delete_image(cub->game->mlx, cub->textures->pixel_ray);
    if (cub->textures->player)
        mlx_delete_image(cub->game->mlx, cub->textures->player);
    player(cub->game, cub);
    ray(cub);
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
    facing_dir(cub);
    cub->game->mlx = mlx_init(WIDTH, cub->game->map_height * TILE, "Cub3D", true);
    if (!cub->game->mlx)
        return (ft_free_struct(cub, 1));
    if (draw_map(cub))
        return (ft_free_struct(cub, 1));
    if (player(cub->game, cub))
        return (ft_free_struct(cub, 1));
    if (ray(cub))
        return (ft_free_struct(cub, 1));
    mlx_key_hook(cub->game->mlx, my_keyhook, cub);
    mlx_loop(cub->game->mlx);
    mlx_terminate(cub->game->mlx);
    return (0);
}

//  FOV 60   \|/ 