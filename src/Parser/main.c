/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:52:20 by hnisirat          #+#    #+#             */
/*   Updated: 2025/09/30 16:36:49 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_config	*cfg;

	if (argc != 2)
	{
		printf("Usage: %s map.cub\n", argv[0]);
		return (1);
	}
	cfg = malloc(sizeof(t_config));
	if (!cfg)
	{
		perror("Failed to allocate memory");
		return (1);
	}
	if (parse_cub(argv[1], cfg))
	{
		printf("Parsing failed\n");
		free_config(cfg);
		return (1);
	}
	printf("Parsing OK\n");
	free_config(cfg);
	free(cfg);
	return (0);
}
