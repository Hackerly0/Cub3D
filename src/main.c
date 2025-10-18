/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:52:20 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/18 17:42:57 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	struct_init(t_cub *cub)
{
	cub->game = malloc(sizeof(t_game));
	cub->rays = malloc(sizeof(t_rays));
	cub->textures = malloc(sizeof(t_textures));
	cub->colors = malloc(sizeof(t_colors));
	cub->dir = malloc(sizeof(t_dir));
	init_struct_element(cub);
	if (!cub->game || !cub->rays || !cub->textures || !cub->colors || !cub->dir)
		return (1);
	return (0);
}

static int	init_cub_struct(t_cub **cub, t_config *cfg)
{
	*cub = malloc(sizeof(t_cub));
	if (!*cub)
	{
		free_config(cfg);
		return (perr("Error:\n Memory allocation failed"));
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
		printf("Error:\n Parsing failed\n");
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
