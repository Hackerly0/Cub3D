/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:25:52 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/13 17:35:02 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	right_ans(char *ans)
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
		if ((a == 'a' && right_ans(qa[1])) || (a == 'b' && right_ans(qa[2]))
			|| (a == 'c' && right_ans(qa[3])) || (a == 'd' && right_ans(qa[4])))
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

void check_if_texture_fail(t_cub *cub)
{
	int i;

	i = 0;
	while(cub->textures->frame_collect[i])
	{
		if (!cub->textures->frame_collect[i])
		{
			printf("Error: Failed to load collectible textures\n");
			ft_free_struct(cub, 1);
			exit(1);
		}
		i++;
	}
	cub->textures->current_collect_frame = 0;
}

void	exit_load(char *path, char *number, char *printed_path, t_cub *cub)
{
	if (path)
		free(path);
	if (number)
		free(number);
	if (printed_path)
		free(printed_path);
	if (cub)
		ft_free_struct(cub , 1);
	exit(1);
}

int load_collectible_textures(t_cub *cub)
{
	int	i;
	char *path;
	char *number;
	char *printed_path;

	i = 0;
	while (i < 21)
	{
		number = ft_itoa(i + 1);
		if (!number)
			exit_load(NULL , NULL, NULL, cub);
		path = ft_strjoin("./textures/open/open_", number);
		if (!path)
			exit_load(NULL, number, NULL, cub);
		printed_path = ft_strjoin (path, ".png");
		if (!printed_path)
			exit_load(path, number, NULL, cub);
		cub->textures->frame_collect[i++] = mlx_load_png(printed_path);
		free(printed_path);
		free(path);
		free(number);
	}
	cub->textures->frame_collect[21] = NULL;
	check_if_texture_fail(cub);
	return (0);
}

// void	show_collect(t_cub *cub)
// {
// 	static int i = 0;
// 	static double last_frame_time = 0;
// 	double current_time;
// 	double frame_delay = 0.2; // Adjust this value: higher = slower animation
	
// 	if (cub->game->show_collect)
// 	{
// 		current_time = mlx_get_time();
		
// 		// Only update frame if enough time has passed
// 		if (current_time - last_frame_time >= frame_delay)
// 		{
// 			cub->textures->door = cub->textures->frame_collect[i];
			
// 			if (i < 2)
// 				i++;
// 			else
// 				i = 0;
			
// 			last_frame_time = current_time;
// 		}
// 	}
// }

mlx_texture_t	*show_collect(t_cub *cub)
{
	static double last_frame_time = 0;
	double current_time;
	double frame_delay = 0.1; // Animation speed: higher = slower
	
	if (cub->game->show_collect)
	{
		current_time = mlx_get_time();
		
		// Update animation frame
		if (current_time - last_frame_time >= frame_delay)
		{
			cub->textures->current_collect_frame++;
			if (cub->textures->current_collect_frame > 20)
			{
				ft_free_struct(cub, 0);
				exit(0);
			}
			last_frame_time = current_time;
		}
		
		// Return the current animation frame
		return (cub->textures->frame_collect[cub->textures->current_collect_frame]);
	}
	
	// If not showing collectible, return normal door texture
	return (cub->textures->door);
}


void	print_scary(int check_x, int check_y, t_cub *cub)
{
	mlx_image_t	*scery_img;
	char		**qa;

	qa = NULL;
	scery_img = mlx_texture_to_image(cub->game->mlx, cub->textures->scery);
	if (cub->game->door_state[check_y][check_x] == '1')
	{
		qa = grab_questions();
		print_qa(qa);
		if (check_answer(qa))
		{
			cub->game->num_doors--;
			if (cub->game->num_doors != 0)
				cub->game->door_state[check_y][check_x] = '0';
		}
		else
		{
			mlx_resize_image(scery_img, WIDTH, HEIGHT);
			mlx_image_to_window(cub->game->mlx, scery_img, 0, 0);
			cub->game->showing_scery = 1;
			cub->game->scery_start_time = mlx_get_time();
		}
	}
	if (cub->game->num_doors == 0)
	{
		cub->game->show_collect = 1;
		// show_collect(cub);
	}
	ft_free(qa, -1);
}

void	toggle_nearest_door(t_cub *cub)
{
	int		check_x;
	int		check_y;
	float	check_dist;

	check_dist = 1.5f;
	check_x = (int)(cub->game->xp_pos + cub->game->dir_x * check_dist);
	check_y = (int)(cub->game->yp_pos + cub->game->dir_y * check_dist);
	if (cub->game->map[check_y][check_x] == 'D')
		print_scary(check_x, check_y, cub);
}

void	space_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		toggle_nearest_door(cub);
}
