/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:18:04 by salshaha          #+#    #+#             */
/*   Updated: 2025/09/10 17:14:53 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

#define BPP sizeof(int32_t)

char *sample_map[] = {
    "1111111111111111111",
    "100000000001111111",
    "100100N000000111111", 
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

// void    player(t_game *game)
// {
    
// }

#define TILE 64
#define P_SIZE 10

void    player(t_game *game)
{
    int i, j;

    i = 0;
    mlx_image_t* player = mlx_new_image(game->mlx, P_SIZE, P_SIZE);
    // memset(player->pixels, 25, player->width * player->height * BPP);
    while (i < P_SIZE)
    {
        j = 0;
        while (j < P_SIZE)
        {
            printf("location: %f", game->xp_pos);
            mlx_put_pixel(player, j, i, 0x00FF00FF);
            j++;
        }
        i++;
    }
    int px = (int)(game->xp_pos * TILE);
    int py = (int)(game->yp_pos * TILE);
    mlx_image_to_window(game->mlx, player, px, py);
}


int main()
{
    t_game *game;
    int i, j;

    game = malloc(sizeof(t_game));
    init_map_from_muhammed(game);
    game->mlx = mlx_init(WIDTH, game->map_height * TILE, "Cub3D", true);
    if (!game->mlx)
        return (1);
    mlx_image_t* wall = mlx_new_image(game->mlx, TILE, TILE);
    // mlx_image_t* player = mlx_new_image(game->mlx, TILE, TILE);
    memset(wall->pixels, 255, wall->width * wall->height * BPP);
    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            if (game->map[i][j] == '1')
            {
                mlx_image_to_window(game->mlx, wall, j * TILE, i * TILE);
            }

            j++;
        }
        i++;
    }
    player(game);
    mlx_loop(game->mlx);
    mlx_terminate(game->mlx);
    return (0);
}


// int     main()
// {
//     t_game *game;
//     int i;
//     int j;

//     j = 0;
//     game = malloc(sizeof(t_game));
//     game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
//     init_map_from_muhammed(game);
//     mlx_image_t* img = mlx_new_image(game->mlx, 32, 32);
//     memset(img->pixels, 255, img->width * img->height * BPP);
//     while (game->map[j])
//     {
//         i = 0;
//         while (game->map[j][i])
//         {
//             if (game->map[j][i] == '1')
//             {
//                     mlx_image_to_window(game->mlx, img, j * 32, i * 32);
//             }
//             i++;
//         }
//         j++;
//     }

//     mlx_loop(game->mlx);
//     return (0);
// }


// int32_t	main(void)
// {
//     // Init mlx with a canvas size of 256x256 and the ability to resize the window.
//     mlx_t* mlx = mlx_init(256, 256, "MLX42", true);
    
//     if (!mlx) exit(EXIT_FAILURE);

//     // Create a 128x128 image.
//     mlx_image_t* img = mlx_new_image(mlx, 128, 128);

//     // Set the channels of each pixel in our image to the maximum byte value of 255. 
//     memset(img->pixels, 255, img->width * img->height * BPP);

//     // Draw the image at coordinate (0, 0).
//     mlx_image_to_window(mlx, img, 0, 0);
//     mlx_image_to_window(mlx, img, 128, 0);

//     // Run the main loop and terminate on quit.  
//     mlx_loop(mlx);
//     mlx_terminate(mlx);

//     return (EXIT_SUCCESS);
// }

