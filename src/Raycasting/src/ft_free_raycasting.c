/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 19:56:49 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/01 21:14:53 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
        if (cub->textures->door)
            mlx_delete_texture(cub->textures->door);
        if (cub->textures->pixel_ray)
            mlx_delete_image(cub->game->mlx, cub->textures->pixel_ray);
        if (cub->textures->player)
            mlx_delete_image(cub->game->mlx, cub->textures->player);
        if (cub->textures->wall) 
            mlx_delete_image(cub->game->mlx, cub->textures->wall);
    }
}

void free_door_states(t_game *game)
{
    int i;
    
    if (game && game->door_state)
    {
        i = 0;
        while (i < game->map_height)
        {
            if (game->door_state[i])
            {
                printf("Freeing door_state row %d\n", i);
                free(game->door_state[i]);
            }
            i++;
        }
        free(game->door_state);
        game->door_state = NULL;
    }
}

int ft_free_struct(t_cub *cub, int type)
{
    if (!cub)
        return (type);
    free_textures(cub);
    free_door_states(cub->game);
    free_map(cub->game);
    if (cub->dir)
    {
        if (cub->dir->north_path)
            free(cub->dir->north_path);
        if (cub->dir->south_path)
            free(cub->dir->south_path);
        if (cub->dir->east_path)
            free(cub->dir->east_path);
        if (cub->dir->west_path)
            free(cub->dir->west_path);
        if (cub->dir->door_path)
            free(cub->dir->door_path);
    }
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
