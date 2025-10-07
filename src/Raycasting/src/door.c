/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:25:52 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/07 16:42:12 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int correct_answer(char *ans)
{
	if (ans[4] == '*')
			return (1);
	return (0);
}

int	check_answer(char **qa)
{
	char	a;
	int		count;

	count = 0;
	while (1)
	{
		printf("\nPlease Enter a valid Choice (a/b/c/d): ");
		scanf(" %c", &a);

		if (a == 'a' && correct_answer(qa[1]))
		{
			count = 0;
			return (1);
		}
		else if (a == 'b' && correct_answer(qa[2]))
		{
			count = 0;
			return (1);	
		}
		else if (a == 'c' && correct_answer(qa[3]))
		{
			count = 0;
			return (1);	
		}
		else if (a == 'd' && correct_answer(qa[4]))
		{
			count = 0;
			return (1);	
		}
		else if (a == 'a' || a == 'b' || a == 'c' || a == 'd')
		{
			count++;
			printf("Wrong Answer!!!!!!!\n");
			if (count == 2)
				return (0);
		}
		else
			printf("Invalid choice, try again.\n");
	}
	return (0);
}

void toggle_nearest_door(t_cub *cub)
{
	int check_x;
	int check_y;
	float check_dist;
	mlx_image_t *scery_img;
	char        **qa;
	
	qa = NULL;
	scery_img = mlx_texture_to_image(cub->game->mlx, cub->textures->scery);
	check_dist = 1.5f; 
	check_x = (int)(cub->game->xp_pos + cub->game->dir_x * check_dist);
	check_y = (int)(cub->game->yp_pos + cub->game->dir_y * check_dist);
	if (cub->game->map[check_y][check_x] == 'D')
	{
		if (cub->game->door_state[check_y][check_x] == '1')
		{
			qa = grab_questions();
			print_qa(qa);
			if(check_answer(qa))
				cub->game->door_state[check_y][check_x] = '0';
			else
			{
				// CREATE AND SHOW THE IMAGE
				scery_img = mlx_texture_to_image(cub->game->mlx, cub->textures->scery);
				mlx_resize_image(scery_img, WIDTH, HEIGHT);
				mlx_image_to_window(cub->game->mlx, scery_img, 0, 0);
				
				// SET THE FLAGS - DON'T SLEEP OR EXIT HERE!
				cub->game->showing_scery = 1;
				cub->game->scery_start_time = mlx_get_time();
			}
		}
	}
	ft_free(qa, -1);
}

void space_hook(mlx_key_data_t keydata, void* param)
{
	t_cub *cub = (t_cub *)param;

	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		toggle_nearest_door(cub);
}

void init_door_states(t_game *game)
{
	int y;
	int x;
	
	game->door_state = malloc(game->map_height * sizeof(char*));
	if (!game->door_state)
		return;
	y = 0;
	while (y < game->map_height)
	{
		game->door_state[y] = malloc(game->map_width + 1);
		if (!game->door_state[y])
			return;
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'D')
				game->door_state[y][x] = '1';
			else
				game->door_state[y][x] = '0';
			x++;
		}
		game->door_state[y][game->map_width] = '\0';
		y++;
	}
}

