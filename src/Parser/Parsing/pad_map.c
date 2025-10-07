/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:53:10 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/07 22:59:17 by hnisirat         ###   ########.fr       */
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

static void	pad_with_spaces(char *new, int start, int width)
{
	while (start < width)
	{
		new[start] = ' ';
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
	pad_with_spaces(new, len, width);
	new[width] = '\0';
	free(old);
	*row_ptr = new;
	return (0);
}
