/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_answers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:19:39 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/18 16:03:18 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_right_mark(const char *s)
{
	if (s && s[4] == '*')
		return (1);
	return (0);
}

int	check_answer(char **qa, t_cub *cub)
{
	char	ans;

	ans = cub->game->ans;
	if ((ans == '1' && has_right_mark(qa[1]))
		|| (ans == '2' && has_right_mark(qa[2]))
		|| (ans == '3' && has_right_mark(qa[3]))
		|| (ans == '4' && has_right_mark(qa[4])))
		return (1);
	if (ans == '1' || ans == '2' || ans == '3' || ans == '4')
	{
		cub->game->wrong_count++;
		printf("Wrong Answer! Attempts: %d/2\n", cub->game->wrong_count);
		if (cub->game->wrong_count >= 2)
			return (0);
		return (-2);
	}
	return (-99);
}

void	handle_correct_answer(t_cub *cub)
{
	clear_question_display(cub);
	cub->game->num_doors--;
	if (cub->game->num_doors != 0)
		cub->game->door_state[cub->game->door_check_y]
		[cub->game->door_check_x] = '0';
	cub->game->question_active = 0;
	cub->game->wrong_count = 0;
	cub->game->ans = '\0';
	ft_free(cub->game->current_qa, -1);
	cub->game->current_qa = NULL;
	ray(cub);
	if (cub->game->num_doors == 0)
		cub->game->show_animated = 1;
}

void	handle_wrong_answer(t_cub *cub)
{
	mlx_image_t	*scery_img;

	clear_question_display(cub);
	scery_img = mlx_texture_to_image(cub->game->mlx, cub->textures->scery);
	mlx_resize_image(scery_img, WIDTH, HEIGHT);
	mlx_image_to_window(cub->game->mlx, scery_img, 0, 0);
	cub->game->showing_scery = 1;
	cub->game->scery_start_time = mlx_get_time();
	cub->game->question_active = 0;
	cub->game->wrong_count = 0;
	cub->game->ans = '\0';
	ft_free(cub->game->current_qa, -1);
	cub->game->current_qa = NULL;
	print_statment_lose();
}

void	process_answer(t_cub *cub)
{
	int	result;

	result = check_answer(cub->game->current_qa, cub);
	if (result == 1)
		handle_correct_answer(cub);
	else if (result == 0)
		handle_wrong_answer(cub);
	else if (result == -2)
	{
		load_new_question(cub);
		cub->game->ans = '\0';
	}
}
