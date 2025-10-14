/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_validation_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:56:09 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/14 22:06:02 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_exists(const char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	validate_file_extension(const char *path, const char *expected_ext)
{
	int		path_len;
	int		ext_len;
	int		result;

	if (!path || !expected_ext)
		return (1);
	path_len = (int)ft_strlen(path);
	ext_len = (int)ft_strlen(expected_ext);
	while (path_len > 0 && (path[path_len - 1] == ' '
			|| path[path_len - 1] == '\t'
			|| path[path_len - 1] == '\n'
			|| path[path_len - 1] == '\r'))
		path_len--;
	if (path_len < ext_len)
		return (1);
	result = ft_strncmp(path + (path_len - ext_len),
			expected_ext, ext_len) != 0;
	return (result);
}

int	validate_texture_file(const char *path)
{
	if (!path)
		return (1);
	if (validate_file_extension(path, ".png"))
	{
		printf("Error\nTexture must be .png format: ");
		if (path)
			printf("%s\n", path);
		else
			printf("(null)\n");
		return (1);
	}
	if (!file_exists(path))
	{
		printf("Error\nTexture file not found or unreadable: %s\n", path);
		return (1);
	}
	return (0);
}
