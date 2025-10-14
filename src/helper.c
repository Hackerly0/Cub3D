/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:47:22 by hnisirat          #+#    #+#             */
/*   Updated: 2025/10/14 22:01:43 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	rgb_to_uint32(t_rgb rgb)
{
	return ((rgb.r << 24) | (rgb.g << 16) | (rgb.b << 8) | 0xFF);
}

int	is_blank_line(const char *s)
{
	size_t	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

void	rtrim(char *s)
{
	size_t	n;

	if (!s)
		return ;
	n = ft_strlen(s);
	while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'
			|| s[n - 1] == ' ' || s[n - 1] == '\t'))
	{
		n--;
		s[n] = '\0';
	}
}

void	trim_fields(char **qa)
{
	int		i;
	size_t	n;

	if (!qa)
		return ;
	i = 0;
	while (qa[i])
	{
		n = ft_strlen(qa[i]);
		while (n > 0 && (qa[i][n - 1] == '\n' || qa[i][n - 1] == '\r'
				|| qa[i][n - 1] == ' ' || qa[i][n - 1] == '\t'))
		{
			n--;
			qa[i][n] = '\0';
		}
		i++;
	}
}
