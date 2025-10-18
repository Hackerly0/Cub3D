/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salshaha <salshaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:53:10 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/18 14:58:58 by salshaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_rowlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	copy_content(char *new, char *old, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new[i] = old[i];
		i++;
	}
}

static void	pad_with_ones(char *new, int start, int width)
{
	while (start < width)
	{
		new[start] = '1';
		start++;
	}
}

int	ft_pad_one_row(char **row_ptr, int width)
{
	char	*old;
	char	*new;
	int		len;

	old = *row_ptr;
	len = ft_rowlen(old);
	if (len >= width)
		return (0);
	new = (char *)malloc((size_t)width + 1);
	if (!new)
		return (1);
	copy_content(new, old, len);
	pad_with_ones(new, len, width);
	new[width] = '\0';
	free(old);
	*row_ptr = new;
	return (0);
}
