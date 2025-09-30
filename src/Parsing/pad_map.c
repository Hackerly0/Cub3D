/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:53:10 by hnisirat          #+#    #+#             */
/*   Updated: 2025/09/30 14:53:11 by hnisirat         ###   ########.fr       */
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

void	ft_fill_spaces(char *dst, int start, int end)
{
	while (start < end)
	{
		dst[start] = '1';
		start++;
	}
}

int	ft_pad_one_row(char **row_ptr, int width)
{
	char	*old;
	char	*new;
	int		len;
	int		i;

	old = *row_ptr;
	len = ft_rowlen(old);
	if (len >= width)
		return (0);
	new = (char *)malloc((size_t)width + 1);
	if (!new)
		return (1);
	i = 0;
	while (i < len)
	{
		new[i] = old[i];
		i++;
	}
	ft_fill_spaces(new, len, width);
	new[width] = '\0';
	free(old);
	*row_ptr = new;
	return (0);
}
