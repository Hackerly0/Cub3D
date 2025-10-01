/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:52:20 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/01 19:15:38 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_config	cfg;
	t_cub		*cub;

	if (argc != 2)
	{
		printf("Usage: %s map.cub\n", argv[0]);
		return (1);
	}
	if (parse_cub(argv[1], &cfg))
	{
		printf("Error: Parsing failed\n");
		free_config(&cfg);
		return (1);
	}
	cub = malloc(sizeof(t_cub));
	if (!cub)
	{
		free_config(&cfg);
		return (perr("Error: Memory allocation failed"));
	}
	if (struct_init(cub))
	{
		free_config(&cfg);
		return (ft_free_struct(cub, 1));
	}
	if (config_to_cub(&cfg, cub))
	{
		free_config(&cfg);
		return (ft_free_struct(cub, 1));
	}
	free_config(&cfg);
	init_door_states(cub->game);
	facing_dir_n_s(cub);
	facing_dir_e_w(cub);
	return (raycasting(cub));
}
