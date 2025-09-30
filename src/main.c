/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:52:20 by hnisirat          #+#    #+#             */
/*   Updated: 2025/09/30 14:52:21 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (argc != 2)
	{
		printf("Usage: %s map.cub\n", argv[0]);
		return (1);
	}
	if (parse_cub(argv[1], &cfg))
	{
		printf("Parsing failed\n");
		free_config(&cfg);
		return (1);
	}
	printf("Parsing OK\n");
	free_config(&cfg);
	return (0);
}
