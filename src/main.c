/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:52:20 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/14 22:14:22 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	init_cub_struct(t_cub **cub, t_config *cfg)
{
	*cub = malloc(sizeof(t_cub));
	if (!*cub)
	{
		free_config(cfg);
		return (perr("Error: Memory allocation failed"));
	}
	if (struct_init(*cub))
	{
		free_config(cfg);
		return (ft_free_struct(*cub, 1));
	}
	if (config_to_cub(cfg, *cub))
	{
		free_config(cfg);
		return (ft_free_struct(*cub, 1));
	}
	return (0);
}

static int	setup_game(char *path, t_cub **cub)
{
	t_config	cfg;

	if (parse_cub(path, &cfg))
	{
		printf("Error: Parsing failed\n");
		free_config(&cfg);
		return (1);
	}
	if (init_cub_struct(cub, &cfg))
		return (1);
	free_config(&cfg);
	facing_dir_n_s(*cub);
	facing_dir_e_w(*cub);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
	{
		printf("Usage: %s map.cub\n", argv[0]);
		return (1);
	}
	if (setup_game(argv[1], &cub))
		return (1);
	return (raycasting(cub));
}
