/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_questions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <hnisirat@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:33:38 by salshaha          #+#    #+#             */
/*   Updated: 2025/10/15 16:12:43 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "../libft/libft.h"
#include "../GNL/get_next_line.h"
#include "cub3d.h"

static int	count_nonblank(const char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_blank_line(line))
			count++;
		free(line);
	}
	close(fd);
	return (count);
}

static char	*get_kth_nonblank(const char *path, int k)
{
	int		fd;
	int		idx;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	idx = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_blank_line(line))
		{
			if (idx == k)
				break ;
			idx++;
		}
		free(line);
	}
	close(fd);
	return (line);
}

static void	seed_once(void)
{
	static int	seeded;

	if (!seeded)
	{
		srand((unsigned int)time(NULL));
		seeded = 1;
	}
}

char	**grab_questions(void)
{
	const char	*path = "questions";
	int			total;
	int			target;
	char		*line;
	char		**qa;

	total = count_nonblank(path);
	if (total <= 0)
		return (NULL);
	seed_once();
	target = rand() % total;
	line = get_kth_nonblank(path, target);
	if (!line)
		return (NULL);
	rtrim(line);
	qa = ft_split(line, ',');
	free(line);
	if (!qa)
		return (NULL);
	trim_fields(qa);
	return (qa);
}

void	print_qa(char **qa)
{
	int	i;
	int	j;

	if (!qa)
		return ;
	i = 0;
	write(1, "\n\n", 2);
	while (qa[i])
	{
		j = 0;
		while (qa[i][j])
		{
			if (ft_isprint(qa[i][j]) && qa[i][j] != '*')
				write(1, &qa[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
